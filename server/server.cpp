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
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if(len == 0) continue;
            if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.
            time_t timestamp;
            time(&timestamp);
            tm* local_time = localtime(&timestamp);
            ostringstream oss;
            oss << put_time(local_time, "%Y%m%d%H%M%S");
            
            string nome_arquivo = "PREFIXO_" + oss.str();

            fs::path p{"../server/"+nome_arquivo};
            fs::ofstream ofs{p};
            ofs.write(buf.data(), len);
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