#include "tcp_connection.hpp"
#include <boost/bind.hpp>

namespace fs = boost::filesystem;

tcp_connection::pointer tcp_connection::create(boost::asio::io_context& io_context, string file, uint16_t max_size) {
    return pointer(new tcp_connection(io_context, file, max_size));
}

tcp::socket& tcp_connection::socket() {
    return socket_;
}

void tcp_connection::start() {
    boost::system::error_code error;

    boost::asio::async_read(socket_, boost::asio::buffer(buf, sizeof(buf)),
                            boost::bind(&tcp_connection::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::handle_read(const boost::system::error_code& error,
                                size_t bytes_transferred) {
    
    fs::fstream ofs( file_full_path_, std::ios::out | std::ios::app);
    

    total_size_file_ +=bytes_transferred;

    if(total_size_file_ > size_file_max_) {
        size_t size_new_file = total_size_file_-size_file_max_;
        size_t new_pos = bytes_transferred-size_new_file;
        ofs.write((char *) buf.data(), new_pos);
        string dst_full_path = original_path_+"_"+to_string(file_sequence_);
        rename(file_full_path_.data(), dst_full_path.data());
        file_sequence_++;
        ofs.close();
        file_full_path_ = original_path_+"_"+to_string(file_sequence_);
        ofs.open( file_full_path_, ios_base::out );
        ofs.write((char *) buf.data()+new_pos, size_new_file);
        total_size_file_=size_new_file;

    } else {
        ofs.write((char *) buf.data(), bytes_transferred);
        ofs.close();
    }

    
    
    start();
}