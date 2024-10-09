#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using boost::asio::ip::tcp;

class Server {

private:
    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
    uint16_t size_file_max;

    static string get_file_name(void);
public:
Server(unsigned short port_num, uint16_t file_size) 
: acceptor(io_context, tcp::endpoint(tcp::v4(), port_num)) {
    cout << "Server running on port " << port_num << endl;
    size_file_max = file_size;
}
void connect(void);

~Server();

};

#endif // SERVER_HPP