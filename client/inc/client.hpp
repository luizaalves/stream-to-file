#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using boost::asio::ip::tcp;

class Client {

private:
    boost::asio::io_context io_context;
    tcp::socket socket;
    tcp::resolver::results_type endpoints;
public:
Client(string ip, string port) : socket(io_context) {
    tcp::resolver resolver(io_context);

    endpoints = resolver.resolve(ip, port);
}

void connect_server(void);
void send_file(string file_to_send);

~Client();

};

#endif // CLIENT_HPP