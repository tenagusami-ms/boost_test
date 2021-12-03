cmake_minimum_required(VERSION 3.1)
project(boost_test CXX)

set(CMAKE_CXX_COMPILER /opt/gcc/bin/c++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -pthread -std=c++20 -fmodules-ts")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
include_directories(
        /home/ec2-user/boost
        /opt/boost/boost
)
link_directories(
        /home/ec2-user/boost/stage/lib
        /opt/boost/boost/stage/lib
)

add_executable(boost_test main.cpp moduleTest.cpp)
target_link_libraries(boost_test boost_system boost_context)
