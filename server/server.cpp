#include "server.hpp"
#include "tcp_server.hpp"
#include <iostream>

void Server::start(uint16_t port, uint16_t size_file_max, uint16_t time_close_conn) {
    try {
        boost::asio::io_context io_context;
        tcp_server server(io_context, port, size_file_max, time_close_conn);

        io_context.run();
    } catch (exception& e) {
        cerr << e.what() << endl;
    }

    return ;
}

Server::~Server() {
    //Destructor    
}