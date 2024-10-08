#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/array.hpp>
#include <iostream>

#include "client.hpp"

using namespace std;
namespace fs = boost::filesystem;
using boost::asio::ip::tcp;
using boost::filesystem::path;

void Client::connect_server(void) {
    try {
        boost::asio::connect(socket, endpoints);
        uint8_t buf[512];
        size_t len;
        fs::path p{file_to_send};
        fs::ifstream ofs{p};
        if(!ofs) return;
        uint16_t bytes_read=512;
        int i=0;
        while(bytes_read==512) {
            ofs.seekg(i);
            ofs.read((char *)buf, sizeof(buf));
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(buf, ofs.gcount()), ignored_error);
            if(ofs.gcount() == 512){
                i+=512;
            }else {
                bytes_read = ofs.gcount();
            }
            memset(buf, 0, 512); 
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