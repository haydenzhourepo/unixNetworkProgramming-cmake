set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# common libraries
link_libraries(unp)

add_executable(daytimetcpcli daytimetcpcli.c)

add_executable(daytimetcpcliv6 daytimetcpcliv6.c)

add_executable(daytimetcpsrv daytimetcpsrv.c)

add_executable(byteorder byteorder.c)

add_executable(daytimetcpsrv1 daytimetcpsrv1.c)
