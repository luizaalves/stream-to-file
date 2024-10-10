#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <iostream>
#include "tcp_connection.hpp"
#include <boost/filesystem/fstream.hpp>

using namespace std;
using boost::asio::ip::tcp;
namespace fs = boost::filesystem;

class tcp_server {
    
private:
    tcp::acceptor acceptor_;
    boost::asio::io_context& io_context_;
    uint16_t max_size_file_;
    boost::filesystem::ofstream* ofs_;

    void start_accept(void);
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);
    static string get_file_name(void);
    string full_file_path();
public:
    tcp_server(boost::asio::io_context& io_context, unsigned short port_num, uint16_t size_file)
    : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), port_num)) {
        max_size_file_ = size_file;
        start_accept();
    }
    uint16_t max_size_file();
};

#endif // TCP_SERVER_HPP