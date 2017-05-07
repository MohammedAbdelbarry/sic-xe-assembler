//
// Created by Mohammed Abdelbarry on 01-May-17.
//

#ifndef SIC_XE_ASSEMBLER_OPERATION_TABLE_H
#define SIC_XE_ASSEMBLER_OPERATION_TABLE_H


class OperationTable {
public:

    /**
     * Returns a static instance of the operation table class itself.
     * @return A singleton instance of the operation table class itself.
     */
    static OperationTable *getInstance();

    /**
     * Checks whether the operation table contains the passed operation or not.
     * @param operation - A string represents the operations which is
     * required to check for its existence in the operation table.
     * @return true if the operation exists else it returns false.
     */
    bool contains(std::string operation);

    /**
     * A getter "accessor" for the information of the passed operation.
     * @param operation - A string represents the operation which is required to get its information
     * from the operation table.
     * @return - An instructionInfo object which contains the information of the passed operation.
     */
    InstructionInfo getInfo(std::string operation);

private:
    static OperationTable *instance;
    std::map<std::string, InstructionInfo> opTable;
    OperationTable();

    /**
     * Initialization function which is responsible for adding operations
     * and their information to the operation table (initializing the operation table)
     * and it is invoked in the constructor of this class.
     */
    void initOpTable();
};


#endif //SIC_XE_ASSEMBLER_OPERATION_TABLE_H
