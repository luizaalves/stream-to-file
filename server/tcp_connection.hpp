#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <boost/filesystem/fstream.hpp>

namespace fs = boost::filesystem;
using namespace std;
using boost::asio::ip::tcp;

class tcp_connection  : public boost::enable_shared_from_this<tcp_connection> {
private:
    tcp_connection(boost::asio::io_context& io_context, string original_path, uint16_t max_size)
    : io_context_(io_context), socket_(io_context_), file_full_path_(original_path), 
    original_path_(original_path), file_sequence_(1), total_size_file_(0), size_file_max_(max_size) {
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    
    boost::array<uint8_t, 128> buf;
    boost::asio::io_context& io_context_;
    tcp::socket socket_;
    string file_full_path_;
    string original_path_;
    int file_sequence_;
    uint16_t total_size_file_;
    uint16_t size_file_max_;
    
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context, string file, uint16_t max_size);
    tcp::socket& socket();
    void start();
};

#endif // TCP_CONNECTION_HPP