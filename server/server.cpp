#include <iostream>
#include "server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

Server::Server(void) {
    //Constructor
}

void Server::connect(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    cout << "Hello, I'm Server" << endl;
    if(server_fd == -1) return;

    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);

    int ret = bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) return;

    ret = listen(server_fd, 5);
    if(ret == -1) return;

    cout << "Waiting conections" << endl;

    socklen_t addrlen = sizeof(addr);
    int client_socket = accept(server_fd, (struct sockaddr *) &addr, &addrlen);
    if(client_socket == -1) return;

    cout << "Connection established" << endl;
    char buffer[1024] = {0};
    ret = recv(client_socket, buffer, 1024, 0);
    if(ret == -1) return;
    time_t timestamp;
    time(&timestamp);
    tm* local_time = localtime(&timestamp);
    ostringstream oss;
    oss << put_time(local_time, "%Y%m%d%H%M%S");
    
    string nome_arquivo = "PREFIXO_" + oss.str();
    ofstream outfile("../server/"+nome_arquivo);
    if (!outfile) return;

    outfile << buffer;
    outfile.close();

    close(client_socket);
    close(server_fd);

    return;
}

Server::~Server() {
    //Destructor    
}