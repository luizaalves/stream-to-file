#include <boost/filesystem/fstream.hpp>
#include <boost/array.hpp>

#include "client.hpp"

#define BUF_SIZE 512

using namespace std;
namespace fs = boost::filesystem;
using boost::asio::ip::tcp;
using boost::filesystem::path;

void Client::connect_server(void) {
    try {
        boost::asio::connect(socket, endpoints);
    } catch (exception& e)
    {
        cerr << e.what() << endl;
    }
}

void Client::send_file(string file_to_send) {
    try
    {
        uint8_t buf[BUF_SIZE];
        size_t len;
        uint16_t bytes_read = BUF_SIZE;
        int blocks_read_from_file = 0;

        fs::path path{file_to_send};
        fs::ifstream ofs{path};
        if(!ofs) return;
        
        boost::system::error_code ignored_error;
        while(bytes_read == BUF_SIZE) {
            ofs.seekg(blocks_read_from_file);
            ofs.read((char *)buf, sizeof(buf));


            boost::asio::write(socket, boost::asio::buffer(buf, ofs.gcount()), ignored_error);

            if(ofs.gcount() == BUF_SIZE){
                blocks_read_from_file+=BUF_SIZE;
            }else {
                bytes_read = ofs.gcount();
            }
            memset(buf, 0, BUF_SIZE); 
        }
        if (ignored_error) {
            cerr << "Erro ao enviar a mensagem: " << ignored_error.message() << std::endl;
        } else {
            cout << "Message sent" << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

Client::~Client() {
    //Destructor    
}