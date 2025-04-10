set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# common libraries
link_libraries(unp)

add_executable(tcpserv01 tcpserv01.c)
add_executable(tcpserv02 tcpserv02.c sigchildwait.c)
add_executable(tcpserv04 tcpserv04.c sigchildwaitpid.c)
add_executable(tcpservselect01 tcpservselect01.c)
add_executable(tcpservpoll01 tcpservpoll01.c)
add_executable(tcpli01 tcpli01.c)
add_executable(tcpcli04 tcpcli04.c)
