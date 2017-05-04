//
// Created by salem.harby on 05/01/2017.
//

#ifndef SIC_XE_ASSEMBLER_SYMBOLTABLE_H
#define SIC_XE_ASSEMBLER_SYMBOLTABLE_H


class SymbolTable {
public:
    void push(std::string label, int address);
    bool contains(std::string label);
    int getAddress(std::string label);

private:
    std::map<std::string, int> symTab;
};


#endif //SIC_XE_ASSEMBLER_SYMBOLTABLE_H
