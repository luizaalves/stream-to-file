cmake_minimum_required(VERSION 3.16)

project(CognyteChallenge)

set(CMAKE_CXX_STANDARD 11)

add_executable(salve_files main.cpp server/server.cpp client/client.cpp)