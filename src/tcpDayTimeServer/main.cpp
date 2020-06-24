#include <iostream>
#include <ctime>
#include <string>

#include "boost/asio.hpp"

std::string makeDayTimeString() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

int main(int argc, char const **argv) {
    try
    {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13));
        for (;;) {
            boost::asio::ip::tcp::socket socket(io_service);
            acceptor.accept(socket);
            std::string message = makeDayTimeString();

            boost::system::error_code ignoredError;
            boost::asio::write(socket, boost::asio::buffer(message), ignoredError);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}