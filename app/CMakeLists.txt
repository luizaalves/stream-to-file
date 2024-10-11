cmake_minimum_required(VERSION 3.16)

project(CognyteChallenge)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

set(BASE_PATH "${CMAKE_BINARY_DIR}")
add_definitions(-DBASE_PATH="${BASE_PATH}")

add_subdirectory(client)
add_subdirectory(server)

add_executable(main_server main_server.cpp)
target_link_libraries(main_server ${Boost_LIBRARIES})
target_link_libraries(main_server PRIVATE server_lib)

add_executable(main_client main_client.cpp)
target_link_libraries(main_client PRIVATE client_lib)