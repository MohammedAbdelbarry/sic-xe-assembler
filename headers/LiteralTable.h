#ifndef SIC_XE_ASSEMBLER_LITERALTABLE_H
#define SIC_XE_ASSEMBLER_LITERALTABLE_H


#include <unordered_map>

class LiteralTable {

public:
    void push(std::string literal, LiteralInfo literalInfo);
    bool contains(std::string literal);
    LiteralInfo &getInfo(std::string literal);
    std::vector<std::string> &getKeySet();

private:
    std::unordered_map<std::string, LiteralInfo> litTab;
    std::vector<std::string> keySet;
};
#endif //SIC_XE_ASSEMBLER_LITERALTABLE_H