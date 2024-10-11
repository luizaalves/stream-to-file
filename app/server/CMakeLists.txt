project(Server)

add_library(server_lib
    src/server.cpp
    inc/server.hpp
    src/tcp_server.cpp
    inc/tcp_server.hpp
    src/tcp_connection.cpp
    inc/tcp_connection.hpp
)

target_include_directories(server_lib PUBLIC inc)