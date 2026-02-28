cmake_minimum_required(VERSION 4.1)
project(TCPServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(TCPServer
        src/main.cpp
        src/server/server.cpp
)
