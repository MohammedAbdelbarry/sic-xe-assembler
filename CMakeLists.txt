cmake_minimum_required(VERSION 3.6)
project(sic_xe_assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES sources/Error.cpp sources/numutil.cpp sources/main.cpp sources/Assembler.cpp
        sources/OperationTable.cpp sources/validator.cpp sources/SymbolTable.cpp
        sources/Line.cpp sources/DirectiveTable.cpp sources/strutil.cpp sources/LiteralTable.cpp)

set(HEADER_FILES headers/Error.h headers/enums.h headers/Line.h headers/strutil.h hea
        headers/numutil.h headers/Assembler.h headers/validator.h headers/DirectiveInfo.h headers/DirectiveTable.h
        headers/InstructionInfo.h headers/OperationTable.h headers/LiteralTable.h)

add_executable(sic_xe_assembler ${SOURCE_FILES})