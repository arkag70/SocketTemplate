cmake_minimum_required(VERSION 3.13)
project(example)
set(CMAKE_CXX_STANDARD 14)


set(SENDER
    src/sender.cpp
)

set(RECEIVER
    src/receiver.cpp
)

include_directories(
    inc
    {CMAKE_SOURCE_DIR}/inc
)

add_executable(sender ${SENDER})
add_executable(receiver ${RECEIVER})

target_link_libraries(sender ethcomlib)
target_link_libraries(receiver ethcomlib)