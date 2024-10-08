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
        boost::array<uint8_t, 128> buf;
        size_t len;
        fs::path p{"../client/test.txt"};
        fs::ifstream ofs{p};
        ofs.read((char *)buf.data(), buf.size());

        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(buf.data(), ofs.gcount()), ignored_error);
        cout << "Message sent" << endl;

    } catch (exception& e)
    {
        cerr << e.what() << endl;
    }
}

Client::~Client() {
    //Destructor    
}