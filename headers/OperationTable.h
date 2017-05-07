/**
 * @file OperationTable.h
 * The file containing the operation table class declaration.
 */
#ifndef SIC_XE_ASSEMBLER_OPERATION_TABLE_H
#define SIC_XE_ASSEMBLER_OPERATION_TABLE_H
/**
 * The operation table singleton class.
 */
class OperationTable {
public:
    /**
     * Gets the operation table singleton instance.
     * @return The operation table singleton instance.
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

    /**
     * A static operation table object which stores the singleton instance to be used in further operations.
     */
    static OperationTable *instance;

    /**
     * A map which stores the operations as keys and its informationInfo objects as values.
     */
    std::map<std::string, InstructionInfo> opTable;

    /**
     * A private default no-args constructor.
     */
    OperationTable();

    /**
     * Initialization function which is responsible for adding operations
     * and their information to the operation table (initializing the operation table)
     * and it is invoked in the constructor of this class.
     */
    void initOpTable();
};


#endif //SIC_XE_ASSEMBLER_OPERATION_TABLE_H
