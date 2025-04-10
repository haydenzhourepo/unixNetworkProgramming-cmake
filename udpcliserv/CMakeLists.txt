set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# common libraries
link_libraries(unp)

add_executable(udpserv01 udpserv01.c)
add_executable(udpcli01 udpcli01.c)
