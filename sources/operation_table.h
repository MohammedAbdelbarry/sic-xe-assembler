//
// Created by Mohammed Abdelbarry on 01-May-17.
//

#ifndef SIC_XE_ASSEMBLER_OPERATION_TABLE_H
#define SIC_XE_ASSEMBLER_OPERATION_TABLE_H


#include "instruction_info.h"
#include <string>
#include <map>

class operation_table {
public:
    std::map<std::string, instruction_info> opTable;
    operation_table& getInstance();

private:
    operation_table instance;
    operation_table();
    void initOpTable();

};


#endif //SIC_XE_ASSEMBLER_OPERATION_TABLE_H
