//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <vector>
#include <fstream>
#include "../headers/Assembler.h"


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
    executePass2(intermediateFile, lines);
}

Assembler::Assembler() {
    //TODO check if we want to add any functionality
}

std::string Assembler::executePass1(std::string fileName, std::map<std::string, std::string> options,
                                    std::vector<Line> &lines) {
    std::string intermediateFile;
    std::string lineString;
    std::ifstream file(fileName);
    //TODO: read first line, check if it begins with (START) and initialize locctr accordingly.
    while (std::getline(file, lineString)) { //TODO: keep reading until reaching a "END" directive or 'EOF'.
        Line line("lol", "lol", "lol"); //TODO: get line by splitting.
        //TODO: check if line is not a comment.
    }
    return intermediateFile;
}

void Assembler::executePass2(std::string intermediateFileName, std::vector<Line> &lines) {
    //TODO implement this method
}
