cmake_minimum_required(VERSION 3.13)  
project(SHARE_ENCRYPTED)               
set(CMAKE_CXX_STANDARD 20)          
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(SOURCE_FILES test.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(C++Server)
add_subdirectory(EncryptionDecryption)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/restbed/distribution/library
                                                ${PROJECT_SOURCE_DIR}/builddir/C++Server
                                                ${PROJECT_SOURCE_DIR}/builddir/EncryptionDecryption
                                                ${PROJECT_SOURCE_DIR}/Client/builddir/utilities)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/restbed/distribution/include
                                                  ${PROJECT_SOURCE_DIR}/C++Server
                                                  ${PROJECT_SOURCE_DIR}/EncryptionDecryption
                                                  ${PROJECT_SOURCE_DIR}/Client/utilities)
                                                  
target_link_libraries(${PROJECT_NAME} restbed server utilities EncryptionDecryption) 

