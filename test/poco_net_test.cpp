#include <iostream>

#include "gtest/gtest.h"
#include "Poco/Net/DNS.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"


class PocoNetTest : public testing::Test {
public:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
private:

};

TEST_F(PocoNetTest, GetHostByName) {
    using Poco::Net::DNS;
    using Poco::Net::IPAddress;
    using Poco::Net::HostEntry;

    const HostEntry& entry = DNS::hostByName("www.baidu.com");
    std::cout << "Canonical Name: " << entry.name() << std::endl;

    const HostEntry::AliasList& aliases = entry.aliases();
    for (HostEntry::AliasList::const_iterator it = aliases.begin();
         it != aliases.end(); ++it) {
        std::cout << "Alias: " << *it << std::endl;
    }

    const HostEntry::AddressList& addrs = entry.addresses();
    for (HostEntry::AddressList::const_iterator it = addrs.begin();
         it != addrs.end(); ++it) {
        std::cout << "Address: " << it->toString() << std::endl;
    }
}

TEST_F(PocoNetTest, StreamSocket) {
    using Poco::Net::SocketAddress;
    using Poco::Net::StreamSocket;
    using Poco::Net::SocketStream;

    using Poco::StreamCopier;
    using Poco::Timespan;

    SocketAddress sa("www.baidu.com", 80);
    StreamSocket socket(sa); // create TCP connection
    // set timeout to forbid hanging
    Timespan timeout(1000000);
    socket.setReceiveTimeout(timeout);

    // I/O streams interface to a StreamSocket
    SocketStream str(socket);

    str << "GET / HTTP/1.1\r\n"
           "Host: www.baidu.com\r\n"
           "\r\n";
    str.flush();

    StreamCopier::copyStream(str, std::cout);
    //std::string result;

    //while (str >> result) {
    //    if (result.empty()) break;
    //    std::cout << result;
    //}
}

