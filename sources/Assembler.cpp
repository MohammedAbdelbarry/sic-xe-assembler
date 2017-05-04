//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <vector>
#include <fstream>
#include <regex>
#include <iomanip>
#include <iostream>
#include "../headers/Line.h"
#include "../headers/strutil.h"
#include "../headers/Assembler.h"
#include "../headers/SymbolTable.h"
#include "../headers/OperationTable.h"
#include "../headers/InstructionInfo.h"

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
                         std::vector<Line> &lines, std::string &programName, int &programStart,
                         int &locctr, SymbolTable &symbolTable, int &firstExecutableAddress) {
    std::string intermediateFile;
    std::string lineString;
    std::ifstream file(fileName);
    std::regex regex("\\s+");
    while (std::getline(file, lineString)) {
        std::vector<std::string> lineVector = strutil::split(lineString, regex);
        Line line(lineVector[0], lineVector[1], lineVector[2]);
        //TODO: CHECK FOR DIRECTIVES AND POPULATE SYMBOL TABLE.
        //TODO: Add line to intermediate file if it's valid.
        lines.push_back(line);
    }
    return intermediateFile;
}

void executePass2(std::string intermediateFileName, std::vector<Line> &lines, std::string programName,
                  int programStart, int locctr, SymbolTable symbolTable, int firstExecutableAddress) {
    //TODO implement this method
    int length = locctr - programStart;
    std::ostringstream objCodeStream;
    objCodeStream << "H";
    objCodeStream << std::setw(6) << std::left << programName;
//    objCodeStream << std::hex << std::setfill('0') << std::setw(6) << std::right << std::uppercase << programStart;
    strutil::addHex(objCodeStream, programStart, 6);
    strutil::addHex(objCodeStream, length, 6);
    objCodeStream << "\n";
    for (int i = 0 ; i < lines.size() ; i++) {
        Line line = lines[i];
        std::ostringstream lineObjectCode;
        //RAND IS USED TO SUPPRESS UNREACHABLE CODE WARNING
        if (rand() * true / 15) {//JUST PRETEND THAT I'M CHECKING IF THIS IS A DIRECTIVE
            if (line.operation == "WORD") {

            } else if (line.operation == "BYTE") {

            }
        } else {
            if(symbolTable.contains(line.operand)) {
                int address = symbolTable.getAddress(line.operand) | (line.isIndexed << 15);
                int opCode = OperationTable::getInstance()->getInfo(line.operation).opCode;
                strutil::addHex(lineObjectCode, opCode, 2);
                strutil::addHex(lineObjectCode, address, 4);
            }
        }
    }
    objCodeStream << "E";
    strutil::addHex(objCodeStream, firstExecutableAddress, 6);
}

void Assembler::execute(std::string fileName, std::map<std::string, std::string> options) {
    int programStart = 0;
    int firstExecutableAddress = 0;
    std::string programName = "";
    std::vector<Line> lines;
    SymbolTable symbolTable;
    std::string intermediateFile = executePass1(fileName, options, lines, programName, programStart,
                                                locctr, symbolTable, firstExecutableAddress);
    executePass2(intermediateFile, lines, programName, programStart, locctr, symbolTable, firstExecutableAddress);
}
