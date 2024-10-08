#include <iostream>
#include "server/server.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Server server(8080);
    server.connect();
    return 0;
}