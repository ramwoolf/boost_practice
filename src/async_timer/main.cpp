#include <iostream>
#include <iomanip>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
    
void async_function(boost::system::error_code const& e_code,
                    boost::asio::steady_timer *t, int *count) 
{
    if (*count < 5) {
        std::cout << '[';
        for (int i = 0; i < 5; ++i) {
            if (i <= *count) {
                std::cout << "####";
            }
            else {
                std::cout << "====";
            }
        }
        std::cout << "]\r" << std::flush;
        ++(*count);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(async_function, boost::asio::placeholders::error, t, count));
    }
    return;
}

int main(int argc, char const **argv) {
    boost::asio::io_context io;
    int count = 0;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
    t.async_wait(boost::bind(async_function, boost::asio::placeholders::error, &t, &count));
    std::cout << "Hello world!" << std::endl;
    io.run();
    std::cout << "Final count is " << std::setw(23) << std::left << count << std::endl;
    return 0;
}