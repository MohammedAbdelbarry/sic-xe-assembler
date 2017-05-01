//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#ifndef SIC_XE_ASSEMBLER_ASSEMBLER_H
#define SIC_XE_ASSEMBLER_ASSEMBLER_H

#include <string>
#include <map>
#include <vector>
#include "Line.h"

class Assembler {

public:
    static Assembler *getInstance();
    void execute(std::string fileName, std::map<std::string, std::string> options);

private:
    Assembler();
    static Assembler *instance;
    std::string executePass1(std::string fileName, std::map<std::string, std::string> options,
                             std::vector<Line> &lines);
    void executePass2(std::string intermediateFileName);
};

#endif //SIC_XE_ASSEMBLER_ASSEMBLER_H
