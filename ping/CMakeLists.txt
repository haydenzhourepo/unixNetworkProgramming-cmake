set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# common libraries
link_libraries(unp)

add_executable(ping main.c readloop.c proc_v4.c init_v6.c proc_v4.c
                proc_v6.c send_v4.c send_v6.c sig_alrm.c)
target_include_directories(ping PRIVATE ./)

add_test(ping ping)