//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#ifndef SIC_XE_ASSEMBLER_ASSEMBLER_H
#define SIC_XE_ASSEMBLER_ASSEMBLER_H

class Assembler {

public:
    static Assembler *getInstance();
    void execute(std::string filePath, std::map<std::string, std::string> options);

private:
    Assembler();
    static Assembler *instance;
    int locCtr;
};

#endif //SIC_XE_ASSEMBLER_ASSEMBLER_H
