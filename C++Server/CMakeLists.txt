cmake_minimum_required(VERSION 3.13)
add_library(server STATIC Server.cpp Service.cpp)


target_link_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/restbed/distribution/library)

target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/restbed/distribution/include)
target_link_libraries(server restbed) 