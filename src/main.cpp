#include <iostream>

#include "server/server.h"

int main() {
    TCPServer::ServerParams params = {
        80,
    };

    TCPServer::Server my_server(params);
}