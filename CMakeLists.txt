cmake_minimum_required(VERSION 3.13)  
project(SHARE_ENCRYPTED)               
set(CMAKE_CXX_STANDARD 17)           

set(SOURCE_FILES test.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(yamlReader)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/restbed/distribution/library
                                                ${PROJECT_SOURCE_DIR}/dependencies/yaml/build
                                                ${PROJECT_SOURCE_DIR}/builddir/yamlReader)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/restbed/distribution/include
                                                  ${PROJECT_SOURCE_DIR}/dependencies/yaml/include                                                  
                                                  ${PROJECT_SOURCE_DIR}/yamlReader/include)

target_link_libraries(${PROJECT_NAME} restbed yamlReader) 

