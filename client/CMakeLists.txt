# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (seven_chat_client)

#将CMAKE_CXX_STANDARD的值定义为14
set(CMAKE_CXX_STANDARD 14)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 util 子目录
add_subdirectory(util)

#
find_package (Threads)
#
find_package(PkgConfig REQUIRED)
#
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
#
include_directories(${GTK3_INCLUDE_DIRS})
#
add_definitions(${GTK3_CFLAGS_OTHER})

#-lpthread
link_directories(/usr/lib/x86_64-linux-gnu)

link_directories(${GTK3_LIBRARY_DIRS})

# 指定生成目标
add_executable(client main.cpp)

# 添加链接库
target_link_libraries(client Util)
target_link_libraries(client pthread)
target_link_libraries (client ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(client ${GTK3_LIBRARIES})
