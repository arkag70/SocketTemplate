cmake_minimum_required(VERSION 3.13)
project(MyList)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE
    src/main.cpp
    src/server.cpp
    src/client.cpp
)
include_directories(inc)

add_executable(app ${SOURCE})