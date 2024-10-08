#include "server.hpp"
#include <boost/array.hpp>

void Server::connect(void) {
    try {
        for (;;) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            cout << buf.data() << endl;
        }
    } catch (exception& e)
    {
        cerr << e.what() << endl;
    }

  return ;
}

Server::~Server() {
    //Destructor    
}