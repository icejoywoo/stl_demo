#include <iostream>

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/SocketAddress.h"

int main(int argc, char** argv) {
    Poco::Net::ServerSocket server(8080);

    for (;;) {
        Poco::Net::StreamSocket ss = server.acceptConnection();
        std::cout << ss.peerAddress().host().toString() << std::endl;
        Poco::Net::SocketStream str(ss);
        str << "HTTP/1.0 200 OK\r\n"
               "Content-Type: text/html\r\n"
               "\r\n"
               "<html><head><title>My First Web Server</title></head>"
               "<body><h1>Hello, World!</h1></body></html>"
            << std::flush;
    }

    return 0;
}
