cmake_minimum_required(VERSION 3.13)  
project(ClientComm)               
set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)         

set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_subdirectory(utilities)
add_subdirectory(yamlReader)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/builddir/utilities
                                                ${PROJECT_SOURCE_DIR}/builddir/yamlReader
                                                ./../builddir/EncryptionDecryption
                                                ./../dependencies/boost/stage/lib)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/utilities
                                                  ${PROJECT_SOURCE_DIR}/yamlReader
                                                  ./../EncryptionDecryption
                                                  ./../dependencies/boost)

target_link_libraries(${PROJECT_NAME} curl curlpp utilities yamlReader EncryptionDecryption libboost_json.a)  

