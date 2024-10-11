#include "tcp_server.hpp"
#include <boost/bind.hpp>
#include <iomanip>

uint16_t tcp_server::max_size_file() {
    return max_size_file_;
}

void tcp_server::start_accept() {
    tcp_connection::pointer new_connection = tcp_connection::create(io_context_, 
                                                full_file_path(), max_size_file_, time_close_conn_);

    acceptor_.async_accept(new_connection->socket(), 
    boost::bind(&tcp_server::handle_accept, this, new_connection,
        boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection,
  const boost::system::error_code& error) {

    if (!error) {
        new_connection->start();
    }

    start_accept();
}

string tcp_server::get_file_name(void) {
    time_t timestamp;
    time(&timestamp);
    tm* local_time = localtime(&timestamp);
    ostringstream oss;
    oss << put_time(local_time, "%Y%m%d%H%M%S");

    string file_name = "PREFIXO_" + oss.str();
    return file_name;
}

string tcp_server::full_file_path() {
    string nome_arquivo = tcp_server::get_file_name();
    string original_path = string(BASE_PATH) +"/../server/"+nome_arquivo;
    return original_path;
}