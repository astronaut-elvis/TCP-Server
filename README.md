# TCP-Server

A lightweight, configurable TCP server written in modern C++20.

Built from scratch using POSIX sockets - no external networking libraries, no frameworks. Just clean, minimal systems code.

---

## Features

- **IPv4 & IPv6** - dual-stack support, switchable via configuration
- **Configurable** - port, backlog depth, and Nagle's algorithm toggle
- **RAII resource management** - socket is automatically closed on destruction
- **Non-copyable design** - prevents accidental resource sharing
- **Clean error handling** - descriptive exceptions on every failure path

## Project Structure

```
TCP-Server/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp
    └── server/
        ├── server.h
        └── server.cpp
```

## Prerequisites

| Requirement | Minimum Version |
|-------------|-----------------|
| C++ Standard | C++20 |
| CMake | 4.1 |
| OS | Linux (POSIX sockets) |
| Compiler | GCC 10+ or Clang 12+ |

## Build & Run

```bash
# Configure
cmake -B build

# Build
cmake --build build

# Run
./build/TCPServer
```

## Configuration

The server is configured through the `ServerParams` struct passed to the constructor:

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `_listen_port` | `int` | `8000` | Port to listen on (1024–65535) |
| `_backlog` | `int` | `10` | Max pending connections in the queue |
| `_ipv6` | `bool` | `false` | Use IPv6 instead of IPv4 |
| `_disable_nagle` | `bool` | `false` | Disable Nagle's algorithm (`TCP_NODELAY`) |

### Example

```cpp
#include "server/server.h"

int main() {
    TCPServer::ServerParams params;
    params._listen_port   = 9090;
    params._ipv6          = true;
    params._disable_nagle = true;

    TCPServer::Server server(params);
    server.Run();
}
```

## Architecture

The server follows a straightforward setup pipeline, executed in the constructor:

```
Server()
  └─ _Setup()
       ├─ _sockSetFd()      // create socket (AF_INET / AF_INET6)
       ├─ _sockSetOpt()     // SO_REUSEADDR, optional TCP_NODELAY
       ├─ _sockBindAddr()   // bind to INADDR_ANY / in6addr_any
       └─ _sockListen()     // start listening with configured backlog
```

After construction, the server is bound and listening. `Run()` will drive the accept loop.

## Roadmap

- [ ] Implement the `Run()` accept loop
- [ ] Add thread pool for concurrent client handling
- [ ] Client read/write abstraction
- [ ] Graceful shutdown (signal handling)
- [ ] TLS support

---

> *"Simplicity is the ultimate sophistication."*
