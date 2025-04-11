set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 添加编译警告选项，提升代码健壮性
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

add_library(unp SHARED unp.c sock_ntop.c wrapsock.c wraplib.c wrapunix.c
                        writen.c str_echo.c str_cli.c readline.c
                        wrapstdio.c signal.c dg_echo.c dg_cli.c
                        tcp_connect.c tcp_listen.c udp_client.c
                        daemon_init.c)
target_include_directories(
        unp
        PUBLIC "${PROJECT_SOURCE_DIR}/include"  # PUBLIC 表示使用该库的目标也包含此路径
)