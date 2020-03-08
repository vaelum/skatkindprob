cmake_minimum_required(VERSION 2.8.9)
project (skatkindprob)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
find_package(Threads)
find_package(GMP)

file(GLOB SOURCES "src/*.cpp")
 
add_executable(skb ${SOURCES})
target_link_libraries (skb ${CMAKE_THREAD_LIBS_INIT} gmp gmpxx)

