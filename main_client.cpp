#include <iostream>
#include "client.hpp"
#include "boost/process/environment.hpp"

#include "client.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    boost::process::environment env = boost::this_process::environment();
    string port = env["PORT"].to_string();
    string ip = env["IP"].to_string();
    string file_path = env["FILE_PATH"].to_string();

    if(port.size() == 0 || ip.size() == 0) return 0;

    Client client(ip, port);
    client.connect_server();
    client.send_file(file_path);
    return 0;
}