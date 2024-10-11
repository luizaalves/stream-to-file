#include <iostream>
#include "server/server.hpp"
#include <boost/process/environment.hpp>

using namespace std;

int main(int argc, char* argv[]) {
    boost::process::environment env = boost::this_process::environment();
    string port = env["PORT"].to_string();
    string max_file_size = env["FILE_SIZE"].to_string();
    string time_close_conn = env["TIME_CLOSE_CONN_SEC"].to_string();
    if(port.size() == 0 || max_file_size.size() == 0 || time_close_conn.size() == 0) return 0;

    Server server;
    server.start((unsigned int)stoi(port), (uint16_t) stoul(max_file_size), stoul(time_close_conn));
    return 0;
}