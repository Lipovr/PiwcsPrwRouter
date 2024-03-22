cmake_minimum_required(VERSION 3.20)

project(PiwcsPrwRouter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(include)
add_subdirectory(src)
