cmake_minimum_required(VERSION 2.8.9)
project (skatkindprob)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
 
add_executable(skb ${SOURCES})