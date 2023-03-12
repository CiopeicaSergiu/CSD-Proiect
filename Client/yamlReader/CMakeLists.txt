cmake_minimum_required(VERSION 3.13)
add_library(yamlReader STATIC Settings.cpp)

target_link_directories(yamlReader PRIVATE ../dependencies/yaml/build)
target_include_directories(yamlReader PUBLIC ../dependencies/yaml/include)
target_link_libraries(yamlReader yaml-cpp)