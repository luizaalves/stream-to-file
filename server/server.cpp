#include "server.hpp"
#include "tcp_server.hpp"
#include <iostream>

void Server::start(uint16_t port, uint16_t size_file_max) {
    try {
        boost::asio::io_service io_service;
        tcp_server server(io_service, port, size_file_max);

        io_service.run();
    } catch (exception& e) {
        cerr << e.what() << endl;
    }

    return ;
}

Server::~Server() {
    //Destructor    
}