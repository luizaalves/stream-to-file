#include <iostream>
#include "client/client.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Client client;
    client.connect_server();
    return 0;
}