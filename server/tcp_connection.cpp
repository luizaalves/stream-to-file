#include "tcp_connection.hpp"
#include <boost/bind.hpp>

namespace fs = boost::filesystem;

tcp_connection::pointer tcp_connection::create(boost::asio::io_context& io_context, string file, uint16_t max_size, uint16_t time_close_conn) {
    return pointer(new tcp_connection(io_context, file, max_size, time_close_conn));
}

tcp::socket& tcp_connection::socket() {
    return socket_;
}

void tcp_connection::start() {
    boost::system::error_code error;
    timer_.expires_after(boost::asio::chrono::seconds(time_close_conn_));

    boost::asio::async_read(socket_, boost::asio::buffer(buf, sizeof(buf)),
                            boost::bind(&tcp_connection::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
    timer_.async_wait([self = shared_from_this()](const boost::system::error_code& e) {
    self->print(e);
    });
}

void tcp_connection::handle_read(const boost::system::error_code& error,
                                size_t bytes_transferred) {
    if(bytes_transferred==0) return;
    
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

void tcp_connection::print(const boost::system::error_code& e) {
  if (timer_.expiry() <= steady_timer::clock_type::now())
    {
      std::cout << "socket close\n";
      socket_.close();
      timer_.cancel();

      timer_.expires_at(steady_timer::time_point::max());
    }

    timer_.async_wait(boost::bind(&tcp_connection::print, shared_from_this(), boost::asio::placeholders::error));
}