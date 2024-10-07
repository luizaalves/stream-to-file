#include <iostream>
#include <sys/socket.h>

#include "client.hpp"

using namespace std;

Client::Client(void) {
    //Constructor
}

void Client::connect(void) {
    cout << "Hello, I'm Client" << endl;
}

Client::~Client() {
    //Destructor    
}