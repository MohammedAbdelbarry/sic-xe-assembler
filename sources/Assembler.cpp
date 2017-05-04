//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <vector>
#include <fstream>
#include <regex>
#include "../headers/Line.h"
#include "../headers/strutil.h"
#include "../headers/Assembler.h"

Assembler *Assembler::instance = nullptr;

Assembler *Assembler::getInstance() {

    if (instance == nullptr)
    {
        instance = new Assembler();
    }
    return instance;
}

Assembler::Assembler() {
    //TODO check if we want to add any functionality
}

std::string executePass1(std::string fileName, std::map<std::string, std::string> options,
                         std::vector<Line> &lines) {
    std::string intermediateFile;
    std::string lineString;
    std::ifstream file(fileName);
    std::regex regex("\\s+");
    while (std::getline(file, lineString)) {
        //TODO: make regex a global field.
        std::vector<std::string> lineVector = strutil::split(lineString, regex);
        Line line(lineVector[0], lineVector[1], lineVector[2]);
        //TODO: CHECK FOR DIRECTIVES AND POPULATE SYMBOL TABLE.
        //TODO: Add line to intermediate file if it's valid.
        lines.push_back(line);
    }
    return intermediateFile;
}

void executePass2(std::string intermediateFileName, std::vector<Line> &lines) {
    //TODO implement this method
}

void Assembler::execute(std::string fileName, std::map<std::string, std::string> options) {
    std::vector<Line> lines;
    std::string intermediateFile = executePass1(fileName, options, lines);
    executePass2(intermediateFile, lines);
}
