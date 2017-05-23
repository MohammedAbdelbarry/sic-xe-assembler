#ifndef SIC_XE_ASSEMBLER_LITERALTABLE_H
#define SIC_XE_ASSEMBLER_LITERALTABLE_H

class LiteralTable {

public:
    void push (std::string literal, LiteralInfo literalInfo);
    bool contains(std::string literal);
    LiteralInfo &getInfo(std::string literal);
    std::map<std::string, LiteralInfo> &getMap();
private:
    std::map<std::string, LiteralInfo> litTab;
};
#endif //SIC_XE_ASSEMBLER_LITERALTABLE_H