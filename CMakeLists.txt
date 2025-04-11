cmake_minimum_required(VERSION 3.22)
project(unixNetworkProgramming)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

add_subdirectory(lib)
add_subdirectory(intro)
add_subdirectory(tcpcliserv)
add_subdirectory(sockopt)
add_subdirectory(udpcliserv)
add_subdirectory(sctp)
add_subdirectory(libgai)