//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <vector>
#include <fstream>
#include "../headers/Assembler.h"
#include "../headers/Line.h"
#include "../headers/operation_table.h"
#include "../headers/validator.h"


Assembler *Assembler::instance = nullptr;

Assembler *Assembler::getInstance() {

    if (instance == nullptr)
    {
        instance = new Assembler();
    }
    return instance;
}

void Assembler::execute(std::string fileName, std::map<std::string, std::string> options) {
    std::vector<Line> lines;
    std::string intermediateFile = executePass1(fileName, options, lines);
    executePass2(intermediateFile);
}

Assembler::Assembler() {
    //TODO check if we want to add any functionality
}

std::string Assembler::executePass1(std::string fileName, std::map<std::string, std::string> options,
                                    std::vector<Line> &lines) {
    std::string intermediateFile;
    std::string lineString;
    std::ifstream file(fileName);
    while (std::getline(file, lineString)) {

    }
    return intermediateFile;
}

void Assembler::executePass2(std::string intermediateFileName) {
    //TODO implement this method
}
