#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/array.hpp>
#include <iostream>

#include "client.hpp"
#define BUF_SIZE 512

using namespace std;
namespace fs = boost::filesystem;
using boost::asio::ip::tcp;
using boost::filesystem::path;

void Client::connect_server(void) {
    try {
        boost::asio::connect(socket, endpoints);
        uint8_t buf[BUF_SIZE];
        size_t len;
        uint16_t bytes_read = BUF_SIZE;
        int blocks_read_from_file = 0;

        fs::path path{file_to_send};
        fs::ifstream ofs{path};
        if(!ofs) return;
        
        while(bytes_read == BUF_SIZE) {
            ofs.seekg(blocks_read_from_file);
            ofs.read((char *)buf, sizeof(buf));

            boost::system::error_code ignored_error;

            boost::asio::write(socket, boost::asio::buffer(buf, ofs.gcount()), ignored_error);

            if(ofs.gcount() == BUF_SIZE){
                blocks_read_from_file+=BUF_SIZE;
            }else {
                bytes_read = ofs.gcount();
            }
            memset(buf, 0, BUF_SIZE); 
        }
        cout << "Message sent" << endl;

    } catch (exception& e)
    {
        cerr << e.what() << endl;
    }
}

Client::~Client() {
    //Destructor    
}