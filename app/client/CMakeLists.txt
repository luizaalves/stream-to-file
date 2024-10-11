project(Client)

add_library(client_lib
    src/client.cpp
    inc/client.hpp
)

target_include_directories(client_lib PUBLIC inc)