#include "server.h"

namespace TCPServer {
    Server::Server(const ServerParams& params)
        :  _params(params), _socket_fd(-1)
    {
        if (params._listen_port < 1024 || params._listen_port > 65535) {
            std::cerr << "Error: port must be between 1024 and 65535." << std::endl;
            throw std::runtime_error("Port must be between 1024 and 65535.");
        }
    }

    Server::~Server() {
        // Handle socket release
    }

    ServerStatus Server::Setup() {
        _socket_fd = _getSocketFd();

        // TODO: Implement other stuff
        return ServerStatus::SUCCESS;
    }

    int Server::_getSocketFd() const {
        const auto domain = _params._ipv6 ? AF_INET6 : AF_INET;
        const auto socket_fd = socket(domain, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            std::cerr << "Error: failed to create socket." << std::endl;
            throw std::runtime_error("Failed to create socket.");
        }
        return socket_fd;
    }
}
