cmake_minimum_required(VERSION 3.13)
project(ethcom_lib)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(ETHCOM ethcomlib)

set(SOURCE
    src/server.cpp
    src/client.cpp
)

include_directories(inc)

add_library(${ETHCOM} STATIC ${SOURCE})

add_subdirectory(examples/linux)