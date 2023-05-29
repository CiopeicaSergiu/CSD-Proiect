cmake_minimum_required(VERSION 3.13)
add_library(EncryptionDecryption STATIC BlowFish.cpp)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)


target_link_directories(EncryptionDecryption PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/boost/stage/lib)

target_include_directories(EncryptionDecryption PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/boost/boost)
                                         
target_link_libraries(EncryptionDecryption ${Boost_LIBRARIES}) 