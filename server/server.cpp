#include "server.hpp"
#include <boost/array.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <iomanip>

namespace fs = boost::filesystem;

void Server::connect(void) {
    try {
        for (;;) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            boost::array<uint8_t, 128> buf;
            boost::system::error_code error;

            string nome_arquivo = get_file_name();
            string original_path = string(BASE_PATH) +"/../server/"+nome_arquivo;
            string dst_full_path = original_path;
            int file_sequence = 1;
            uint16_t total_size_file = 0;

            fs::path file_path(dst_full_path);
            
            fs::fstream ofs( file_path, ios_base::out );

            while(error != boost::asio::error::eof) {
                size_t len_read = socket.read_some(boost::asio::buffer(buf), error);
                if(len_read==0) break;
                total_size_file+=len_read;
                if (error && error != boost::asio::error::eof)
                    throw boost::system::system_error(error); // Some other error.
                
                if(total_size_file > size_file_max) {
                    size_t size_new_file = total_size_file-size_file_max;
                    size_t new_pos = len_read-size_new_file;

                    ofs.write((char *) buf.data(), new_pos);
                    
                    dst_full_path = original_path+"_"+to_string(file_sequence);
                    rename(original_path.data(), dst_full_path.data());
                    file_sequence++;
                    ofs.close();
                    dst_full_path = original_path+"_"+to_string(file_sequence);
                    file_path = dst_full_path;
                    ofs.open( file_path, ios_base::out );
                    ofs.write((char *) buf.data()+new_pos, size_new_file);
                    total_size_file=size_new_file;
                }
                else ofs.write((char *) buf.data(), len_read);
                memset(buf.data(), 0, buf.size()); 
            }
        }
    } catch (exception& e)
    {
        cerr << e.what() << endl;
    }

  return ;
}

Server::~Server() {
    //Destructor    
}

string Server::get_file_name(void) {
    time_t timestamp;
    time(&timestamp);
    tm* local_time = localtime(&timestamp);
    ostringstream oss;
    oss << put_time(local_time, "%Y%m%d%H%M%S");
    
    string file_name = "PREFIXO_" + oss.str();
    return file_name;
}