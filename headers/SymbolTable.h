//
// Created by salem.harby on 05/01/2017.
//

#ifndef SIC_XE_ASSEMBLER_SYMBOLTABLE_H
#define SIC_XE_ASSEMBLER_SYMBOLTABLE_H


class SymbolTable {
public:

    /**
     * Adds a label with its address to the map of the symbol table.
     * @param label - A label which is required to be added to the symbol table.
     * @param address - An address for the passed label to be added to the symbol table.
     */
    void push(std::string label, int address);

    /**
     * Checks whether this passed label is defined (exists in the symbol table) or not.
     * @param label - A label which is required to check for its existence in the symbol table.
     * @return true if the label exits in the symbol table else it returns false.
     */
    bool contains(std::string label);

    /**
     * A getter "accessor" for the address of a this passed label.
     * @param label - A label which is required to get its address.
     * @return the address of the passed label.
     */
    int getAddress(std::string label);

private:
    std::map<std::string, int> symTab;
};

#endif //SIC_XE_ASSEMBLER_SYMBOLTABLE_H
