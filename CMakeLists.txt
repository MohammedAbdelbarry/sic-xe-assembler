cmake_minimum_required(VERSION 3.6)
project(sic_xe_assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES sources/main.cpp sources/Assembler.cpp)

add_executable(sic_xe_assembler ${SOURCE_FILES})