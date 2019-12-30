# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (seven_chat_server)

#将CMAKE_CXX_STANDARD的值定义为14
set(CMAKE_CXX_STANDARD 14)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(include)

find_package (Threads)

#-lmysqlclient
link_directories(/usr/lib/x86_64-linux-gnu/)
#-lpthread
link_directories(/usr/lib/x86_64-linux-gnu)

# 指定生成目标
add_executable(server main.cpp)

# 添加链接库
target_link_libraries(server Database_server)
target_link_libraries(server mysqlclient)
target_link_libraries(server pthread)
target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})
