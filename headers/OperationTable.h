//
// Created by Mohammed Abdelbarry on 01-May-17.
//

#ifndef SIC_XE_ASSEMBLER_OPERATION_TABLE_H
#define SIC_XE_ASSEMBLER_OPERATION_TABLE_H


class OperationTable {
public:
    static OperationTable *getInstance();
    bool contains(std::string operation);
    InstructionInfo getInfo(std::string operation);

private:
    static OperationTable *instance;
    std::map<std::string, InstructionInfo> opTable;
    OperationTable();
    void initOpTable();
};


#endif //SIC_XE_ASSEMBLER_OPERATION_TABLE_H
