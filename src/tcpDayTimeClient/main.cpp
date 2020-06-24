#include <iostream>

#include "boost/asio.hpp"
#include "boost/array.hpp"

int main(int argc, char const **argv) {
    try
    { 
        if (argc != 2) {
            std::cerr << "Usage: client <host>\n";
            return 1;
        }

        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(argv[1], "daytime");
        boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

        boost::asio::ip::tcp::socket socket(io_service);
        boost::asio::connect(socket, endpointIterator);

        for (;;) {
            boost::array<char, 128> buf;
            boost::system::error_code errorCode;
            std::size_t len = socket.read_some(boost::asio::buffer(buf), errorCode);
            if (errorCode == boost::asio::error::eof) {
                break;
            }
            else if (errorCode) {
                throw boost::system::system_error(errorCode);
            }

            std::cout.write(buf.data(), len);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}