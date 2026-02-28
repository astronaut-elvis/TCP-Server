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
        if (_socket_fd >= 0) {
            close(_socket_fd);
        }
    }

    ServerStatus Server::Run() {
        // TODO: Implement run logic
        return ServerStatus::SUCCESS;
    }

    ServerStatus Server::_Setup() {
        _sockSetFd();
        _sockSetOpt();
        _sockBindAddr();
        _sockListen();
        return ServerStatus::SUCCESS;
    }

    void Server::_sockSetFd() {
        const auto domain = _params._ipv6 ? AF_INET6 : AF_INET;
        const auto socket_fd = socket(domain, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
        }
        _socket_fd = socket_fd;
    }

    void Server::_sockSetOpt() const {
        int opt = 1;

        if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            throw std::runtime_error("Failed to set SO_REUSEADDR: " + std::string(strerror(errno)));
        }

        if (_params._disable_nagle) {
            if (setsockopt(_socket_fd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt)) < 0) {
                throw std::runtime_error("Failed to set TCP_NODELAY: " + std::string(strerror(errno)));
            }
        }
    }
    void Server::_sockBindAddr() const {
        sockaddr_storage addr_storage{};
        socklen_t addr_length{};

        if (!_params._ipv6) {
            auto* addr = reinterpret_cast<sockaddr_in*>(&addr_storage);
            addr->sin_family = AF_INET;
            addr->sin_port = htons(_params._listen_port);
            addr->sin_addr.s_addr = htonl(INADDR_ANY);
            addr_length = sizeof(sockaddr_in);
        } else {
            auto* addr = reinterpret_cast<sockaddr_in6*>(&addr_storage);
            addr->sin6_family = AF_INET6;
            addr->sin6_port = htons(_params._listen_port);
            addr->sin6_addr = in6addr_any;
            addr_length = sizeof(sockaddr_in6);
        }

        if (bind(_socket_fd, reinterpret_cast<sockaddr*>(&addr_storage), addr_length) < 0) {
            throw std::runtime_error("Failed to bind to IPv4 port " +
                                     std::to_string(_params._listen_port) + ": " +
                                     std::string(strerror(errno)));
        }

    }

    void Server::_sockListen() const {
        if (listen(_socket_fd, _params._backlog)) {
            throw std::runtime_error("Failed to listen on port " +
                                     std::to_string(_params._listen_port) + ": " +
                                     std::string(strerror(errno)));
        }
    }
}
