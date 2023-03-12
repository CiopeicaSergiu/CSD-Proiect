cmake_minimum_required(VERSION 3.13)  
project(SHARE_ENCRYPTED)               
set(CMAKE_CXX_STANDARD 17)           

set(SOURCE_FILES test.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(yamlReader)
add_subdirectory(C++Server)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/restbed/distribution/library
                                                ${PROJECT_SOURCE_DIR}/dependencies/yaml/build
                                                ${PROJECT_SOURCE_DIR}/builddir/yamlReader
                                                ${PROJECT_SOURCE_DIR}/builddir/C++Server
                                                ${PROJECT_SOURCE_DIR}/Client/builddir/utilities)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/restbed/distribution/include
                                                  ${PROJECT_SOURCE_DIR}/dependencies/yaml/include                                                  
                                                  ${PROJECT_SOURCE_DIR}/yamlReader
                                                  ${PROJECT_SOURCE_DIR}/C++Server
                                                  ${PROJECT_SOURCE_DIR}/Client/utilities)

target_link_libraries(${PROJECT_NAME} restbed yamlReader server utilities) 

