#include <iostream>
#include "client/client.hpp"
#include "server/server.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Client client;
    client.connect();
    Server server;
    server.connect();
    return 0;
}