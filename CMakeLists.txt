cmake_minimum_required(VERSION 3.7)
project(sic_xe_assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES sources/main.cpp)

add_executable(sic_xe_assembler ${SOURCE_FILES})