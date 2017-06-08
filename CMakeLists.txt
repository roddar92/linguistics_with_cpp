cmake_minimum_required(VERSION 3.6)
project(ngramdictionary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/ngramdictionary/main.cpp src/ngramdictionary/NGramDictionaryManager.cpp src/ngramdictionary/NGramDictionaryManager.hpp)
add_executable(ngramdictionary ${SOURCE_FILES})