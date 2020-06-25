#include <iostream>
#include <ctime>
#include <string>

#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/enable_shared_from_this.hpp"

std::string makeDayTimeString() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
    public:
    using pointer = boost::shared_ptr<TcpConnection>;

    static pointer create(boost::asio::execution_context &context) {
        return pointer(new TcpConnection(context));
    }

    boost::asio::ip::tcp::socket& socket() {
        return mSocket;
    }

    void start() {
        mMessage = makeDayTimeString();
        boost::asio::async_write(mSocket, boost::asio::buffer(mMessage),
        boost::bind(&TcpConnection::handleWrite, shared_from_this(), 
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }

    private:
    TcpConnection(boost::asio::execution_context &context) 
    : mSocket(context)
    {}

    void handleWrite(boost::system::error_code const& /* error */, std::size_t /* bytes transferred */)
    {}

    boost::asio::ip::tcp::socket mSocket;
    std::string mMessage;
};

class TcpServer {
    public:
    TcpServer(boost::asio::execution_context &context) 
    : mAcceptor(context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13))
    {
        startAccept();
    }
    private:
    void startAccept() {
        TcpConnection::pointer newConnection = TcpConnection::create(mAcceptor.get_executor().context());
        mAcceptor.async_accept(newConnection->socket(),
                                boost::bind(&TcpServer::handleAccept, this, newConnection,
                                            boost::asio::placeholders::error));
    }

    void handleAccept(TcpConnection::pointer newConnection, boost::system::error_code const& error) {
        if (!error) {
            newConnection->start();
        }
        startAccept();
    }

    boost::asio::ip::tcp::acceptor mAcceptor;
};

int main(int argc, char const **argv) {
    try
    {
        boost::asio::execution_context context;
        boost::asio::io_context ioContext;
        TcpServer server(context);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}