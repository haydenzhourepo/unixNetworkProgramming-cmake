set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# common libraries
link_libraries(unp)

# set this to let cmake find the .pc files
set(CMAKE_PREFIX_PATH "/home/hayden/learn/c/libpcap/install")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPCAP REQUIRED libpcap)

add_executable(udpcksum main.c pcap.c udpcksum.c udpread.c udpwrite.c
        senddnsquery-raw.c cleanup.c)
target_include_directories(udpcksum PRIVATE ${LIBPCAP_INCLUDE_DIRS} ./)
message(STATUS  "found ${LIBPCAP_LINK_LIBRARIES}")
target_link_libraries(udpcksum PRIVATE ${LIBPCAP_LINK_LIBRARIES})

add_test(udpcksum udpcksum)