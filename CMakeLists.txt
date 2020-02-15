cmake_minimum_required(VERSION 3.15)
project(CppTelegramBots)

set(CMAKE_CXX_STANDARD 20)

# Uncomment for linux if you have issues with cpprestsdk_DIR
# set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

find_package(cpprestsdk REQUIRED)

add_executable(CppTelegramBots src/main.cpp)
include_directories(src)

target_link_libraries(CppTelegramBots PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal)

file(COPY resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)

IF(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release mode")
ENDIF(CMAKE_BUILD_TYPE MATCHES Release)
