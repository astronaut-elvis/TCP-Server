#ifndef TCPSERVER_SERVER_H
#define TCPSERVER_SERVER_H

#include <iostream>

#include <cstdint>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_BACKLOG_LENGTH 10

namespace TCPServer {

    enum class ServerStatus {
        SUCCESS,
        FAILURE
    };

    typedef struct ServerParamsDef {
        int  _listen_port    = 8000;
        int  _backlog        = DEFAULT_BACKLOG_LENGTH;
        bool _ipv6           = false;
        bool _disable_nagle  = false;
    } ServerParams;

    class Server {
    public:
        explicit Server(const ServerParams& params = ServerParams());
        ~Server();

        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;

        ServerStatus Run();

    private:
        ServerStatus _Setup();

        void _sockSetFd();
        void _sockSetOpt() const;
        void _sockBindAddr() const;
        void _sockListen() const;

        ServerParams _params;
        int _socket_fd;
    };

}
#endif