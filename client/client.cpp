#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "client.hpp"

using namespace std;

Client::Client(void) {
    //Constructor
}

void Client::connect_server(void) {
    cout << "Hello, I'm Client" << endl;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    cout << server_fd << endl;
    if(server_fd == -1) return;

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    char buffer[1024] = "Enviando mensagem pro servidor...";
    cout << buffer << endl;

    int ret = connect(server_fd, (struct sockaddr *) &server_addr, (socklen_t) sizeof(server_addr));
    cout << ret << endl;

    ret = send(server_fd, &buffer, strlen(buffer), 0);
    cout << ret << endl;
}

Client::~Client() {
    //Destructor    
}