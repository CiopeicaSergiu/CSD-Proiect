cmake_minimum_required(VERSION 3.13)
add_library(utilities STATIC Utilities.cpp)


target_link_directories(utilities PRIVATE ./../../dependencies/boost/stage/lib)

target_include_directories(utilities PUBLIC ./../../dependencies/boost)

target_link_libraries(utilities libboost_json.a)  