#include <iostream>
#include <boost/asio.hpp>


#include "client.hpp"

using namespace std;
using boost::asio::ip::tcp;


void Client::connect_server(void) {
    try {
        boost::asio::connect(socket, endpoints);
 
        string message = "hello server, I'm client";

        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        cout << "Message sent" << endl;

    } catch (exception& e)
    {
        cerr << e.what() << endl;
    }
}

Client::~Client() {
    //Destructor    
}