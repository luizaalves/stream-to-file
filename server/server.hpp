#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>

using namespace std;

class Server {

private:
public:
Server() {
}
void start(uint16_t port, uint16_t size_file_max);

~Server();

};

#endif // SERVER_HPP