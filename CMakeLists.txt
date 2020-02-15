cmake_minimum_required(VERSION 3.15)
project(CppTelegramBots)

set(CMAKE_CXX_STANDARD 20)
set(LIBS -lboost_system)
# Uncomment for linux if you have issues with cpprestsdk_DIR or with Boost filesystem
# set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
# find_package(Boost COMPONENTS system filesystem REQUIRED)

find_package(cpprestsdk REQUIRED)

add_executable(CppTelegramBots src/main.cpp)
include_directories(src)

target_link_libraries(CppTelegramBots PRIVATE cpprestsdk::cpprest ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

file(COPY resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)

IF(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release mode")
ENDIF(CMAKE_BUILD_TYPE MATCHES Release)
