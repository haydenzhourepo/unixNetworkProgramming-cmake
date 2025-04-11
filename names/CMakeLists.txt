set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# common libraries
link_libraries(unp)

add_executable(ndaytimetcpsrv1 daytimetcpsrv1.c)
add_executable(ndaytimetcpcli daytimetcpcli.c)
