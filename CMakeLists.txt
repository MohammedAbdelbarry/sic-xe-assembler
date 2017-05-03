cmake_minimum_required(VERSION 3.6)
project(sic_xe_assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES sources/main.cpp sources/Assembler.cpp sources/OperationTable.cpp sources/validator.cpp headers/validator.h sources/SymbolTable.cpp headers/SymbolTable.h sources/Line.cpp headers/Line.h sources/DirectiveTable.cpp headers/DirectiveTable.h)

add_executable(sic_xe_assembler ${SOURCE_FILES})