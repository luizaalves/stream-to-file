#include <iostream>
#include "client/client.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Client client("127.0.0.1", "8080");
    client.connect_server();
    return 0;
}