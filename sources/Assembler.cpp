//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <vector>
#include <fstream>
#include <regex>
#include <iomanip>
#include <iostream>
#include "../headers/enums.h"
#include "../headers/Line.h"
#include "../headers/Error.h"
#include "../headers/strutil.h"
#include "../headers/Assembler.h"
#include "../headers/SymbolTable.h"
#include "../headers/InstructionInfo.h"
#include "../headers/OperationTable.h"
#include "../headers/validator.h"
#include "../headers/DirectiveInfo.h"
#include "../headers/DirectiveTable.h"
#include "../headers/util.h"

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

Line constructLine(std::vector<std::string> lineVector) {
    for (int i = lineVector.size(); i < 4; i++)
        lineVector.push_back("");
    Line line(lineVector[0], lineVector[1], lineVector[2]);
    return line;
}

void addHexBytes(std::ostringstream &stream, std::string &bytes, int numBytes) {
    for (char ch : bytes) {
        numBytes--;
        strutil::addHex(stream, ch, 2);
    }
    while (numBytes--) {
        strutil::addHex(stream, 0, 2);
    }
}

std::string executePass1(std::string fileName, std::map<std::string, std::string> options,
                         std::vector<Line> &lines, std::string &programName, int &programStart,
                         int &locCtr, SymbolTable &symbolTable, int &firstExecutableAddress) {

    std::string intermediateFile;
    std::string lineString;
    std::ifstream fileStream(fileName);
    std::regex regex("\\s+");
    int instructionSize[4] = {3, 3, 3, 4};
    //Read first line
    std::getline(fileStream, lineString);
    Line line = constructLine(strutil::split(lineString, regex));
    if (line.operation == "START") {
        try {
            validator::validateLine(line);
            DirectiveTable::getInstance()->getInfo("START").execute(locCtr, line);
            line.locCtr = locCtr;
            programStart = firstExecutableAddress = locCtr; //TODO: temporary.
            if (line.label.empty()) {
                programName = line.label;
                symbolTable.push(line.label, line.locCtr);
            }
        } catch (ErrorMessage errorMessage) {
            line.error = new Error(errorMessage);
        }
        std::cout << locCtr << "\t" << line << std::endl;
        lines.push_back(line);
    } else
        fileStream.seekg(fileStream.beg);

    while (std::getline(fileStream, lineString)) {
        Line line = constructLine(strutil::split(lineString, regex));
        //TODO: ignore if it's a comment line, or stop if it's an 'END' directive (DEBATABLE).
        try {
            validator::validateLine(line);
            std::cout << locCtr << "\t" << line << std::endl;
            if (DirectiveTable::getInstance()->contains(line.operation)) {
                //Directive line.
                line.locCtr = locCtr;
                DirectiveTable::getInstance()->getInfo(line.operation).execute(locCtr, line);
                line.mnemonicType = MnemonicType::DIRECTIVE;
                if (symbolTable.contains(line.label))
                    line.error = new Error(ErrorMessage::INVALID_LABEL);
                else
                    symbolTable.push(line.label, locCtr);
            } else { //Instruction line.
                line.mnemonicType = MnemonicType::INSTRUCTION;
                for (InstructionFormat instructionFormat : OperationTable::getInstance()
                        ->getInfo(line.operation).supportedFormats) {
                    line.lineFormat = instructionFormat;
                    try {
                        validator::validateFormat(line);
                        line.locCtr = locCtr;
                        locCtr += instructionSize[instructionFormat];
                        if (line.error != nullptr) {
                            delete line.error;
                            line.error = nullptr;
                        }
                        break;
                    } catch (ErrorMessage errorMessage) {
                        line.error = new Error(errorMessage);
                    }
                }
            }
            //TODO: Add line to intermediate fileStream if it's valid (line.error has some value).
        } catch (ErrorMessage errorMessage) {
            line.error = new Error(errorMessage);
        }
        lines.push_back(line);
    }
    return intermediateFile;
}

void executePass2(std::string intermediateFileName, std::vector<Line> &lines, std::string programName,
                  int programStart, int locCtr, SymbolTable symbolTable, int firstExecutableAddress) {
    //TODO implement this method
    const int MAX_LINE_LENGTH = 30;
    int startingAddress = lines[1].locCtr;
    std::cout << lines[0].operation << std::endl;
    int length = locCtr - startingAddress;
    std::ostringstream objCodeStream;
    objCodeStream << "H";
//    objCodeStream << std::setw(6) << std::left << programName;
    objCodeStream << std::setw(6) << std::left;
    objCodeStream << programName;
//    objCodeStream << std::hex << std::setfill('0') << std::setw(6) << std::right << std::uppercase << programStart;
    strutil::addHex(objCodeStream, startingAddress, 6);
    strutil::addHex(objCodeStream, length, 6);
    objCodeStream << "\n";
    int initLocCtr = startingAddress;
    std::string curRecord;
    objCodeStream << "T";
    strutil::addHex(objCodeStream, initLocCtr, 6);
    for (int i = 1 ; i < lines.size() ; i++) {
        Line line = lines[i];
        std::ostringstream lineObjectCode;
        if (line.locCtr >= initLocCtr + MAX_LINE_LENGTH) {
            strutil::addHex(objCodeStream, curRecord.length() / 2, 2);
            objCodeStream << curRecord;
            objCodeStream << "\n";
            curRecord = "";
            initLocCtr = line.locCtr;
            objCodeStream << "T";
            strutil::addHex(objCodeStream, initLocCtr, 6);
        }
        if (!OperationTable::getInstance()->contains(line.operation)) {
            if(line.operation == "WORD" || line.operation == "BYTE") {
                int numBytes = 0;
                int numHalfBytes = 0;
                bool done = false;
                int locCtr = line.locCtr;
                if (line.operation == "WORD") {
                    numBytes = 3;
                } else if (line.operation == "BYTE") {
                    numBytes = 1;
                }
                numHalfBytes = numBytes << 1;
                if (util::Hexadecimal::isHexLiteral(line.operand)) {
                    std::string hexLiteral = util::Hexadecimal::parseHexadecimalLiteral(line.operand);
                    for (int j = 0; j < hexLiteral.length(); j += numHalfBytes) {
                        std::ostringstream curObjCode;
                        locCtr += numHalfBytes;
                        std::string seg = hexLiteral.substr(j, numHalfBytes);
                        if (locCtr < initLocCtr + MAX_LINE_LENGTH) {
                            curObjCode << std::hex << std::setfill('0');
                            curObjCode << std::setw(numHalfBytes) << std::right << std::uppercase << seg;
                        } else {
                            strutil::addHex(objCodeStream, curRecord.length() / 2, 2);
                            objCodeStream << curRecord;
                            objCodeStream << "\n";
                            curRecord = "";
                            initLocCtr = locCtr;
                            objCodeStream << "T";
                            strutil::addHex(objCodeStream, initLocCtr, 6);
                            curObjCode << std::hex << std::setfill('0');
                            curObjCode << std::setw(numHalfBytes) << std::right << std::uppercase << seg;
                        }
                        lineObjectCode << curObjCode.str();
                        curRecord += curObjCode.str();
                    }
                } else if (strutil::isCharLiteral(line.operand)) {
                    std::string charLiteral = strutil::parseCharLiteral(line.operand);
                    for (int j = 0; j < charLiteral.length(); j += numBytes) {
                        std::ostringstream curObjCode;
                        locCtr += numBytes;
                        std::string seg = charLiteral.substr(j, numBytes);
                        if (locCtr < initLocCtr + MAX_LINE_LENGTH) {
                            addHexBytes(curObjCode, seg, numBytes);
                        } else {
                            strutil::addHex(objCodeStream, curRecord.length() / 2, 2);
                            objCodeStream << curRecord;
                            objCodeStream << "\n";
                            curRecord = "";
                            initLocCtr = locCtr;
                            objCodeStream << "T";
                            strutil::addHex(objCodeStream, initLocCtr, 6);
                            addHexBytes(curObjCode, seg, numBytes);
                        }
                        lineObjectCode << curObjCode.str();
                        curRecord += curObjCode.str();
                    }
                }
                std::cout << line << '\t' << lineObjectCode.str() << std::endl;
            }
        } else {
            int opCode = OperationTable::getInstance()->getInfo(line.operation).opCode;
            strutil::addHex(lineObjectCode, opCode, 2);
            switch(line.lineFormat) {
                case ONE:
                    strutil::addHex(lineObjectCode, 0, 4);
                    break;
                case TWO:
                    break;
                case THREE:
                    if(symbolTable.contains(line.operand)) {
                        int address = symbolTable.getAddress(line.operand) | (line.isIndexed << 15);
                        strutil::addHex(lineObjectCode, address, 4);
                    } else {
                        //TODO: ERROR!!!!
                        std::cout << "ERROR: symbol \"" << line.operand;
                        std::cout << "\" at line: " << i << std::endl;
                    }
                    break;
                case FOUR:
                    break;
            }
        }
        curRecord += lineObjectCode.str();
    }
    objCodeStream << "\n";
    objCodeStream << "E";
    strutil::addHex(objCodeStream, firstExecutableAddress, 6);
    std::cout << objCodeStream.str() << std::endl;
}

void Assembler::execute(std::string fileName, std::map<std::string, std::string> options) {
    int firstExecutableAddress = locCtr = 0;
    int programStart = 0;
    std::string programName = "";
    std::vector<Line> lines;
    SymbolTable symbolTable;
    std::string intermediateFile = executePass1(fileName, options, lines, programName, programStart,
                                                locCtr, symbolTable, firstExecutableAddress);
    executePass2(intermediateFile, lines, programName, programStart, locCtr, symbolTable, firstExecutableAddress);
}

void addLiterals(std::string literalValue, int numBytes, int &locCtr, int &initLocCtr,
                 std::ostringstream &lineObjectCode, std::ostringstream &objCodeStream, std::string &curRecord) {
    const int MAX_LINE_LENGTH = 30;
    for (int j = 0; j < literalValue.length(); j += numBytes) {
        std::ostringstream curObjCode;
        locCtr += numBytes;
        if (locCtr < initLocCtr + MAX_LINE_LENGTH) {
            curObjCode << std::hex << std::setfill('0');
            curObjCode << std::setw(numBytes) << std::right << std::uppercase << literalValue.substr(j, numBytes);
            lineObjectCode << curObjCode.str();
            curRecord += curObjCode.str();
        } else {
            strutil::addHex(objCodeStream, curRecord.length() / 2, 2);
            objCodeStream << curRecord;
            objCodeStream << "\n";
            curRecord = "";
            initLocCtr = locCtr;
            objCodeStream << "T";
            strutil::addHex(objCodeStream, initLocCtr, 6);
        }
    }
}

