#ifndef TCPSERVER_SERVER_H
#define TCPSERVER_SERVER_H

#include <iostream>

#include <cstdint>
#include <sys/socket.h>

namespace TCPServer {

    enum class ServerStatus {
        SUCCESS,
        FAILURE
    };

    typedef struct ServerParamsDef {
        int  _listen_port = 8000;
        bool _ipv6 = false;
    } ServerParams;

    class Server {
    public:
        explicit Server(const ServerParams& params = ServerParams());
        ~Server();

        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;

        ServerStatus Setup();
        ServerStatus Run();

    private:
        [[nodiscard]] int _getSocketFd() const;

        /*
         * Parameters
         */
        ServerParams _params;
        int _socket_fd;
    };

}
#endif