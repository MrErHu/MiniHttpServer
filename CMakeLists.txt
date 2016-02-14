cmake_minimum_required(VERSION 3.3)
project(MiniHttpServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RequestMessage.cpp RequestMessage.h ServerTool.cpp ServerTool.h ResponseMessage.cpp ResponseMessage.h)
add_executable(MiniHttpServer ${SOURCE_FILES})