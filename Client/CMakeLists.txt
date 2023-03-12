cmake_minimum_required(VERSION 3.13)  
project(Client)               
set(CMAKE_CXX_STANDARD 17)           

set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_subdirectory(utilities)
add_subdirectory(yamlReader)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/builddir/utilities
                                                ${PROJECT_SOURCE_DIR}/builddir/yamlReader)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/utilities
                                                  ${PROJECT_SOURCE_DIR}/yamlReader)

target_link_libraries(${PROJECT_NAME} curl curlpp utilities yamlReader) 

