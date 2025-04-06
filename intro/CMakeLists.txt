set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 添加编译警告选项，提升代码健壮性
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

add_executable(daytimetcpcli daytimetcpcli.c)
target_link_libraries(daytimetcpcli PRIVATE unp)

add_executable(daytimetcpcliv6 daytimetcpcliv6.c)
target_link_libraries(daytimetcpcliv6 PRIVATE unp)

add_executable(daytimetcpsrv daytimetcpsrv.c)
target_link_libraries(daytimetcpsrv PRIVATE unp)

add_executable(byteorder byteorder.c)
target_link_libraries(byteorder PRIVATE unp)
