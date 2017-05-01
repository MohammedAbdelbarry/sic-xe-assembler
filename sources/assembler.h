#ifndef SIC_XE_ASSEMBLER_ASSEMBLER_H
#define SIC_XE_ASSEMBLER_ASSEMBLER_H

#include <string>
#include <map>

namespace assembler {
    void executePass1(std::string fileName, std::map<std::string, std::string> options);
    void executePass2(std::string intermediateFileName);
};


#endif //SIC_XE_ASSEMBLER_ASSEMBLER_H
