#include <iostream>
#include <boost/asio.hpp>

void async_function(boost::system::error_code const& e_code) {
    std::cout << "Hello world!" << std::endl;
    return;
}

int main(int argc, char const **argv) {
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    t.async_wait(&async_function);
    std::cout << "Hello world!" << std::endl;
    io.run();
    std::cout << "HERE" << std::endl;
    return 0;
}