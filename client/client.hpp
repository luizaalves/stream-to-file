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
    string file_to_send;
public:
Client(string ip, string port, string path_file) : socket(io_context) {
    tcp::resolver resolver(io_context);
    file_to_send = path_file;

    endpoints = resolver.resolve(ip, port);
}

void connect_server(void);

~Client();

};

#endif // CLIENT_HPP