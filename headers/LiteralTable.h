/**
 * @file LiteralTable.h
 * The file containing the literal table class declaration.
 */
#ifndef SIC_XE_ASSEMBLER_LITERALTABLE_H
#define SIC_XE_ASSEMBLER_LITERALTABLE_H

#include <unordered_map>
/**
 * The literal table class.
 */
class LiteralTable {

public:
    /**
    * Adds a literal to the literal table.
    * @param literal - A literal which is required to be added to the literal table.
    * @param literalInfo - A LiteralInfo object which holds the properties of the passed
     * literal to be added to the literal table.
    */
    void push(std::string literal, LiteralInfo literalInfo);
    /**
     * Checks whether this passed literal exists in the literal table or not.
     * @param literal - A literal which is required to check for its existence in the literal table.
     * @return true if the literal exits in the literal table else it returns false.
     */
    bool contains(std::string literal);
    /**
     * A getter "accessor" for the LiteralInfo object of this passed literal.
     * @param literal - A literal which is required to get its info.
     * @return the info of the passed literal.
     */
    LiteralInfo &getInfo(std::string literal);
    /**
     * A getter "accessor" for the key set used in holding literals' keys in order.
     * @return A key set which represents the literals' keys in order.
     */
    std::vector<std::string> &getKeySet();

private:
    /**
     * A map which stores the literals' hexadecimal strings as keys and its LiteralInfo class objects as values.
     */
    std::unordered_map<std::string, LiteralInfo> litTab;
    /**
     * A vector which stores the literals' hexadecimal strings "keys" to keep the order of literals.
     */
    std::vector<std::string> keySet;
};
#endif //SIC_XE_ASSEMBLER_LITERALTABLE_H