cmake_minimum_required(VERSION 2.8)
project(UImain_temp)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(UImain_temp main.cpp actwithface.cpp handle.cpp LogSign.cpp LogSign.h setting.cpp setting.h UImain.cpp UImain.h client.h util/cJSON.c util/cJSON.h)


target_link_libraries (UImain_temp ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(UImain_temp ${GTK3_LIBRARIES})