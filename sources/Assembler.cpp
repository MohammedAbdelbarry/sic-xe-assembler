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
    if (lineVector.size() > 1) {
        if (OperationTable::getInstance()->contains(lineVector[1])
            && OperationTable::getInstance()->getInfo(lineVector[1]).supportedFormats[0]
               == InstructionFormat::ONE) {
            if(lineVector.size() > 3) {
                lineVector[2].append(lineVector[3]);
                lineVector[3] = lineVector[2];
                lineVector[2] = "";
            } else if (lineVector.size() > 2)
                lineVector[2] = "";
        }
        for (int i = lineVector.size(); i < 4; i++)
            lineVector.push_back("");
        Line line(lineVector[0], lineVector[1], lineVector[2], lineVector[3]);
        if (strutil::endsWith(strutil::toUpper(line.operand), ",X")) {
            line.operand = line.operand.substr(0, line.operand.size() - 2);
            line.isIndexed = true;
        }
        return line;
    } else {
        Line line(lineVector[0]);
        return line;
    }
}

void appendToIntermediateFile(std::string &intermediateFile, Line line) {
    std::ostringstream intermediateStream;
    intermediateStream << line;

    if (line.error != nullptr) {
        intermediateStream << "\t";
        intermediateStream << *line.error;
    }
    intermediateStream << "\n";
    intermediateFile.append(intermediateStream.str());
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

void initRecord(std::ostringstream &stream, int &initLocCtr, int recordLength, std::string &curRecord, int curLocCtr) {
    strutil::addHex(stream, recordLength, 2);
    stream << curRecord;
    stream << "\n";
    curRecord = "";
    initLocCtr = curLocCtr;
    stream << "T";
    strutil::addHex(stream, initLocCtr, 6);
}

std::string executePass1(std::string fileName, std::map<std::string, std::string> options,
                         std::vector<Line> &lines, std::string &programName, int &programStart,
                         int &locCtr, SymbolTable &symbolTable, int &firstExecutableAddress) {
    std::string intermediateFile;
    std::string lineString;
    std::ifstream fileStream(fileName);
    std::regex regex("\\s+");
    std::streampos firstLinePos = fileStream.tellg();
    int instructionSize[4] = {3, 3, 3, 4};
    //Read first line
    while (std::getline(fileStream, lineString)) {
        Line firstLine = constructLine(strutil::split(lineString, regex, 3));
        if (firstLine.getLineType() == LineType::COMMENT) {
            firstLinePos = fileStream.tellg();
            continue;
        }
        if (strutil::toUpper(firstLine.operation) == "START") {
            try {
                validator::validateLine(firstLine);
                DirectiveTable::getInstance()->getInfo("START").execute(locCtr, firstLine);
                firstLine.locCtr = locCtr;
                programStart = locCtr;
                if (!firstLine.label.empty()) {
                    programName = firstLine.label;
                    symbolTable.push(firstLine.label, firstLine.locCtr);
                }
            } catch (Error* error) {
                firstLine.error = error;
            }
            lines.push_back(firstLine);
            appendToIntermediateFile(intermediateFile, firstLine);
        } else
            fileStream.seekg(firstLinePos);
        break;
    }
    //Read rest of the lines.
    while (std::getline(fileStream, lineString)) {
        Line line = constructLine(strutil::split(lineString, regex));
        //TODO: ignore if it's a comment line, or stop if it's an 'END' directive (DEBATABLE).
        if (line.getLineType() == LineType::COMMENT) {
            appendToIntermediateFile(intermediateFile, line);
            lines.push_back(line);
            continue;
        }
        if (!line.label.empty()) {
            if (symbolTable.contains(line.label))
                line.error = new Error(ErrorType::INVALID_LABEL, line.label);
            else
                symbolTable.push(line.label, locCtr);
        }
        try {
            validator::validateLine(line);
            if (DirectiveTable::getInstance()->contains(line.operation)) { //Directive line.
                line.mnemonicType = MnemonicType::DIRECTIVE;
                if (strutil::toUpper(line.operation) == "START") {
                    line.locCtr = locCtr;
                    line.error = new Error(ErrorType::DUPLICATE_START, line.operation);
                } else if (strutil::toUpper(line.operation) == "END") {
                    line.locCtr = locCtr;
                    if (symbolTable.contains(line.operand))
                        firstExecutableAddress = symbolTable.getAddress(line.operand);
                    else
                        line.error = new Error(ErrorType::INVALID_OPERAND, line.operand);
                    appendToIntermediateFile(intermediateFile, line);
                    lines.push_back(line);
                    break;
                } else {
                    line.locCtr = locCtr;
                    DirectiveTable::getInstance()->getInfo(line.operation).execute(locCtr, line);
                }
            } else { //Instruction line.
                line.mnemonicType = MnemonicType::INSTRUCTION;
                for (InstructionFormat instructionFormat : OperationTable::getInstance()
                        ->getInfo(line.operation).supportedFormats) {
                    line.lineFormat = instructionFormat;
                    try {
                        line.locCtr = locCtr;
                        validator::validateFormat(line);
                        locCtr += instructionSize[instructionFormat];
                        if (line.error != nullptr) {
                            delete line.error;
                            line.error = nullptr;
                        }
                        break;
                    } catch (Error *error) {
                        line.error = error;
                    }
                }
            }
        } catch (Error *error) {
            line.locCtr = locCtr;
            line.error = error;
        }
        appendToIntermediateFile(intermediateFile, line);
        lines.push_back(line);
    }
    return intermediateFile;
}

std::string executePass2(std::string intermediateFileName, std::vector<Line> &lines, std::string programName,
                  int programStart, int locCtr, SymbolTable symbolTable, int firstExecutableAddress) {
    const int MAX_LINE_LENGTH = 30;
    const int MAX_SIC_MEMORY = 1 << 15;
    int length = locCtr - programStart;
    std::ostringstream objCodeStream;
    objCodeStream << "H";
    objCodeStream << std::setw(6) << std::left;
    objCodeStream << strutil::toUpper(programName);
    strutil::addHex(objCodeStream, programStart, 6);
    strutil::addHex(objCodeStream, length, 6);
    objCodeStream << "\n";
    int initLocCtr = programStart;
    bool startNewLine = false;
    std::string curRecord;
    objCodeStream << "T";
    strutil::addHex(objCodeStream, initLocCtr, 6);
    std::ostringstream errors;
    for (int i = 1 ; i < lines.size() ; i++) {
        Line line = lines[i];
        if (line.error) {
            errors << "Error: " << line.error->errorType;
            errors << " at Line: " + i << std::endl;
            continue;
        }
        std::ostringstream lineObjectCode;
        if (!OperationTable::getInstance()->contains(line.operation)) {
            if(strutil::toUpper(line.operation) == "WORD" || strutil::toUpper(line.operation) == "BYTE") {
                if (line.locCtr >= initLocCtr + MAX_LINE_LENGTH || startNewLine) {
                    startNewLine = false;
                    initRecord(objCodeStream, initLocCtr, curRecord.length() / 2, curRecord, line.locCtr);
                }
                int numBytes = 0;
                int numHalfBytes = 0;
                int locCtr = line.locCtr;
                if (strutil::toUpper(line.operation) == "WORD") {
                    numBytes = 3;
                } else if (strutil::toUpper(line.operation) == "BYTE") {
                    numBytes = 1;
                }
                numHalfBytes = numBytes << 1;
                if (util::Hexadecimal::isHexLiteral(line.operand)) {
                    std::string hexLiteral = util::Hexadecimal::parseHexadecimalLiteral(line.operand);
                    for (int j = 0; j < hexLiteral.length(); j += numHalfBytes) {
                        locCtr += numHalfBytes;
                        std::string seg = hexLiteral.substr(j, numHalfBytes);
                        if (locCtr > initLocCtr + MAX_LINE_LENGTH) {
                            curRecord += lineObjectCode.str();
                            initRecord(objCodeStream, initLocCtr, curRecord.length() / 2, curRecord, locCtr);
                            lineObjectCode.str("");
                        }
                        lineObjectCode << std::hex << std::setfill('0');
                        lineObjectCode << std::setw(numHalfBytes) << std::right << std::uppercase << seg;
                    }
                } else if (strutil::isCharLiteral(line.operand)) {
                    std::string charLiteral = strutil::parseCharLiteral(line.operand);
                    for (int j = 0; j < charLiteral.length(); j += numBytes) {
                        locCtr += numBytes;
                        std::string seg = charLiteral.substr(j, numBytes);
                        if (locCtr <= initLocCtr + MAX_LINE_LENGTH) {
                            addHexBytes(lineObjectCode, seg, numBytes);
                        } else {
                            curRecord += lineObjectCode.str();
                            initRecord(objCodeStream, initLocCtr, curRecord.length() / 2, curRecord, locCtr);
                            lineObjectCode.str("");
                            addHexBytes(lineObjectCode, seg, numBytes);
                        }
                    }
                } else if (strutil::toUpper(line.operation) == "WORD") {
                    try {
                        strutil::addHex(lineObjectCode, std::stoi(line.operand), 6);
                    } catch (std::invalid_argument ex) {
                        errors << "ERROR: operand \"" << line.operand;
                        errors << "\" is not a valid operand. At line: " << i + 1 << std::endl;
                    }
                } else {
                    errors << "ERROR: operand \"" << line.operand;
                    errors << "\" is not a valid operand. At line: " << i + 1 << std::endl;
                }
            } else if (strutil::toUpper(line.operation) == "RESB" || strutil::toUpper(line.operation) == "RESW") {
                startNewLine = true;
            }
        } else {
            if (line.locCtr >= initLocCtr + MAX_LINE_LENGTH || startNewLine) {
                startNewLine = false;
                initRecord(objCodeStream, initLocCtr, curRecord.length() / 2, curRecord, line.locCtr);
            }
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
                        errors << "ERROR: symbol \"" << line.operand;
                        errors << "\" not found. At line: " << i + 1 << std::endl;
                    }
                    break;
                case FOUR:
                    break;
            }
        }
        int recLen = curRecord.length();
        int lineLen = lineObjectCode.str().length();
        if ((recLen + lineLen) / 2 > MAX_LINE_LENGTH) {
            initRecord(objCodeStream, initLocCtr, curRecord.length() / 2, curRecord, line.locCtr);
        }
        curRecord += lineObjectCode.str();
    }
    if (!curRecord.empty()) {
        strutil::addHex(objCodeStream, curRecord.length() / 2, 2);
        objCodeStream << curRecord;
    } else {
        throw std::invalid_argument(errors.str());
    }
    objCodeStream << "\n";
    objCodeStream << "E";
    strutil::addHex(objCodeStream, firstExecutableAddress, 6);
    if (errors.str().empty()) {
        return objCodeStream.str();
    } else {
        throw errors.str();
    }
}

void writeFile(std::string filePath, std::string data) {
    std::ofstream fileStream(filePath);
    fileStream << data;
}

void Assembler::execute(std::string filePath, std::map<std::string, std::string> options) {
    int firstExecutableAddress = locCtr = 0;
    int programStart = 0;
    std::string programName = "";
    std::vector<Line> lines;
    SymbolTable symbolTable;
    std::string intermediateFile = executePass1(filePath, options, lines, programName, programStart,
                                                locCtr, symbolTable, firstExecutableAddress);
    std::cout << intermediateFile;
    writeFile(fileutil::removeExtension(filePath) + " - inter.txt", intermediateFile);
    std::string objFile = executePass2(intermediateFile, lines, programName,
                                       programStart, locCtr, symbolTable, firstExecutableAddress);
    writeFile(fileutil::removeExtension(filePath) + ".obj", objFile);
    std::cout << objFile;
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

