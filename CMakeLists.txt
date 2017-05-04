cmake_minimum_required(VERSION 3.6)
project(sic_xe_assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES sources/util.cpp sources/main.cpp sources/Assembler.cpp
        sources/OperationTable.cpp sources/validator.cpp sources/SymbolTable.cpp
        sources/Line.cpp sources/DirectiveTable.cpp sources/strutil.cpp headers/strutil.h)

add_executable(sic_xe_assembler ${SOURCE_FILES})