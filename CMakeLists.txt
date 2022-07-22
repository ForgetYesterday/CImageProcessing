cmake_minimum_required(VERSION 3.15)
project(CImageProcessing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(CImageProcessing ${SOURCE_FILES})