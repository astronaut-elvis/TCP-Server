#include <iostream>

#include "server/server.h"

int main() {
    auto params = std::make_shared<TCPServer::ServerParams>();
    TCPServer::Server my_server(*params);
}