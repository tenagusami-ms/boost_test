cmake_minimum_required(VERSION 3.1)
project(boost_test CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -pthread -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
include_directories(/home/ec2-user/boost_1_77_0)
link_directories($/home/ec2-user/boost_1_77_0/stage/lib)

add_executable(boost_test main.cpp)
target_link_libraries(boost_test boost_system boost_coroutine)
