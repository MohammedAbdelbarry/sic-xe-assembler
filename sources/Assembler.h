//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#ifndef SIC_XE_ASSEMBLER_ASSEMBLER_H
#define SIC_XE_ASSEMBLER_ASSEMBLER_H

#include <string>
#include <map>

class Assembler {

public:
    ~Assembler();
    static Assembler *getInstance();
    void execute(std::string fileName, std::map<std::string, std::string> options);

private:
    Assembler();

    std::string executePass1(std::string fileName, std::map<std::string, std::string> options);
    void executePass2(std::string intermediateFileName);

};

#endif //SIC_XE_ASSEMBLER_ASSEMBLER_H
