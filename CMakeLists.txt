cmake_minimum_required(VERSION 3.23)
project(regex)

set(CMAKE_CXX_STANDARD 11)
include_directories(${LUA_INCLUDE_PATH})
link_libraries(lua)
link_directories(${LUA_LIB_PATH})

add_library(regex SHARED library.cpp regex.cpp regex_constants.cpp match_results.cpp regex_algorithm.cpp regex.hpp regex_iterator.cpp)
set_target_properties(regex PROPERTIES PREFIX "")
