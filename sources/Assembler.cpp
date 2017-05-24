/**
 * @file Assembler.cpp
 * The file containing the assembler class implementation.
 */

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
#include "../headers/numutil.h"
#include "../headers/LiteralInfo.h"
#include "../headers/LiteralTable.h"

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
/**
 * Constructs and returns a new line.
 * @param lineVector A vector containing the split source code lines.
 * @return The constructed line.
 */
Line constructLine(std::vector<std::string> lineVector) {
    if (lineVector.size() > 1) {
        if (OperationTable::getInstance()->contains(lineVector[1])
            && OperationTable::getInstance()->getInfo(lineVector[1]).supportedFormats[0]
               == InstructionFormat::ONE || lineVector[1] == "LTORG") {
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
/**
 * Appends a line to the intermediate file.
 * @param intermediateFile A string containing the intermediate file.
 * @param line The line to be appended.
 */
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
/**
 * Adds all the characters in the strings as bytes to the output stream
 * in hex.
 * @param stream The string stream containing the object code.
 * @param bytes The string containing the bytes to be appended.
 * @param numBytes The number of bytes to be appended.
 */
void addHexBytes(std::ostringstream &stream, std::string &bytes, int numBytes) {
    for (char ch : bytes) {
        numBytes--;
        strutil::addHex(stream, ch, 2);
    }
    while (numBytes--) {
        strutil::addHex(stream, 0, 2);
    }
}
/**
 * Initializes a new record in the object code.
 * @param stream The output stream containing the object code.
 * @param initLocCtr  The value of the location counter in the record.
 * @param recordLength The length of the record.
 * @param curRecord The current record that will be appended.
 * @param curLocCtr The current value of the location counter.
 */
void initRecord(std::ostringstream &stream, int &initLocCtr, int recordLength, std::string &curRecord, int curLocCtr) {
    strutil::addHex(stream, recordLength, 2);
    stream << curRecord;
    stream << "\n";
    curRecord = "";
    initLocCtr = curLocCtr;
    stream << "T";
    strutil::addHex(stream, initLocCtr, 6);
}

void addLiteral(std::string &operand, LiteralTable &literalTable, int &literalLabelCounter) {
    LiteralInfo literalInfo;
    std::string literalString = operand;
    literalString.erase(literalString.begin()); // removing the '=' character.
    if (numutil::Hexadecimal::isHexLiteral(literalString)) {
        literalInfo.literal = literalString;
        literalString = numutil::Hexadecimal::parseHexadecimalLiteral(literalString);
        literalInfo.literalDirective = LiteralDirective::BYTE;
    } else if (strutil::isCharLiteral(literalString)) {
        literalInfo.literal = literalString;
        literalString = strutil::parseCharLiteral(literalString);
        literalInfo.literalDirective = LiteralDirective::BYTE;
        literalString = strutil::toHex(literalString);
    } else {
        literalString = numutil::Decimal::parseDecimalLiteral(literalString);
        literalInfo.literal = literalString;
        literalInfo.literalDirective = LiteralDirective::WORD;
        literalString = numutil::Decimal::toHex(std::stoi(literalString));
    }
    if(!literalTable.contains(literalString)) {
        operand = "$" + std::to_string(literalLabelCounter);
        literalInfo.label = operand;
        literalTable.push(strutil::toUpper(literalString), literalInfo);
        literalLabelCounter++;
    } else {
        operand = literalTable.getInfo(literalString).label;
    }
}

void resolveLiterals(LiteralTable &literalTable, std::vector<Line> &lines, int &locCtr,
                     std::string &intermediateFile, SymbolTable &symbolTable) {
    LiteralInfo literalInfo;
    Line line;
    for (std::vector<std::string>::iterator iterator = literalTable.getKeySet().begin();
            iterator != literalTable.getKeySet().end() ; iterator++) {
        if (!literalTable.getInfo(*iterator).resolved) {
            literalInfo = literalTable.getInfo(*iterator);
            literalTable.getInfo(*iterator).resolved = true;
            if (literalInfo.literalDirective == LiteralDirective::BYTE) {
                line = Line(literalInfo.label, "BYTE", literalInfo.literal, "");
            } else {
                line = Line(literalInfo.label, "WORD", literalInfo.literal, "");
            }
            line.locCtr = locCtr;
            symbolTable.push(line.label, locCtr);
            DirectiveTable::getInstance()->getInfo(line.operation).execute(locCtr, line, symbolTable);
            lines.push_back(line);
            appendToIntermediateFile(intermediateFile, line);
        } else {
            continue;
        }
    }
}
/**
 * Executes pass one on the object code and returns the intermediate file.
 * @param fileName The name of the file to be assembled.
 * @param options The command line options.
 * @param lines A vector that will have all the lines in the source code added to it.
 * @param programName A string that will have the name of the program assigned to it.
 * @param programStart An in that will have the starting index of the program
 * assigned to it.
 * @param locCtr An int representing the location counter.
 * @param symbolTable A table that will have all the symbols and their respective
 * addresses added to it.
 * @param firstExecutableAddress An int that will have the first executable address
 * in the source code assigned to it.
 * @return A string containing the intermediate file.
 */
std::string executePass1(std::string fileName, std::map<std::string, std::string> options,
                         std::vector<Line> &lines, std::string &programName, int &programStart,
                         int &locCtr, LiteralTable &literalTable, SymbolTable &symbolTable,
                         int &firstExecutableAddress, int &literalTableCounter) {
    std::string intermediateFile;
    std::string lineString;
    std::ifstream fileStream(fileName);
    std::regex regex("\\s+(?=(?:[^']*'[^']*')*[^']*$)");
    std::streampos firstLinePos = fileStream.tellg();
    int instructionSize[4] = {3, 3, 3, 4};

    //Read first line
    while (std::getline(fileStream, lineString)) {
        Line firstLine = constructLine(strutil::split(lineString, regex));
        if (firstLine.getLineType() == LineType::COMMENT) {
            firstLinePos = fileStream.tellg();
            continue;
        }
        if (strutil::toUpper(firstLine.operation) == "START") {
            try {
                validator::validateLine(firstLine);
                DirectiveTable::getInstance()->getInfo("START").execute(locCtr, firstLine, symbolTable);
                firstLine.locCtr = locCtr;
                firstExecutableAddress = programStart = locCtr;
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
                    if (!line.operand.empty()) {
                        if (symbolTable.contains(line.operand))
                            firstExecutableAddress = symbolTable.getAddress(line.operand);
                        else
                            DirectiveTable::getInstance()->getInfo("END").execute(firstExecutableAddress, line, symbolTable);
                    }
                    //Invalid label for END operation.
                    if (!line.label.empty()) {
                        line.error = new Error(ErrorType::INVALID_LABEL, line.label);
                    }
                    appendToIntermediateFile(intermediateFile, line);
                    lines.push_back(line);
                    break;
                } else if (strutil::toUpper(line.operation) == "LTORG") {
                    line.locCtr = locCtr;
                    DirectiveTable::getInstance()->getInfo("LTORG").execute(locCtr, line, symbolTable);
                    appendToIntermediateFile(intermediateFile, line);
                    lines.push_back(line);
                    resolveLiterals(literalTable, lines, locCtr, intermediateFile, symbolTable);
                    continue;
                } else {
                    line.locCtr = locCtr;
                    DirectiveTable::getInstance()->getInfo(line.operation).execute(locCtr, line, symbolTable);
                }
            } else { //Instruction line.
                line.mnemonicType = MnemonicType::INSTRUCTION;
                //Calling Literal add function.
                if (line.operand[0] == '=') {
                    addLiteral(line.operand, literalTable, literalTableCounter);
                }
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
    resolveLiterals(literalTable, lines, locCtr, intermediateFile, symbolTable);
    return intermediateFile;
}
/**
 * Initializes the header record and appends it to the object code
 * output stream.
 * @param stream The output stream containing the object code.
 * @param programName The name of the program.
 * @param initLocCtr The initial location counter.
 * @param programLength The length of the program.
 */
void initHeader(std::ostringstream &stream, std::string programName, int initLocCtr, int programLength) {
    stream << "H";
    stream << std::setw(6) << std::left;
    stream << strutil::toUpper(programName);
    strutil::addHex(stream, initLocCtr, 6);
    strutil::addHex(stream, programLength, 6);
    stream << "\n";
}
/**
 * Adds the end record to the object code stream.
 * @param stream The object code stream.
 * @param firstExecutableAddress The first executable address in the assembly program.
 */
void addEndRecord(std::ostringstream &stream, int firstExecutableAddress) {
    stream << "E";
    strutil::addHex(stream, firstExecutableAddress, 6);
}
/**
 * Writes a string to a file.
 * @param filePath The path of the file.
 * @param data The string to be written.
 */

void writeFile(std::string filePath, std::string data) {
    std::ofstream fileStream(filePath);
    fileStream << data;
}

void writeListingFile(std::string &filePath, std::vector<Line> &lines) {
    std::cout << "\n\nListing File:\n";
    std::ostringstream stream;
    for(Line line : lines) {
        stream << line << std::endl;
    }
    std::string listingFile = stream.str();
    std::cout << listingFile << std::endl;
    writeFile(fileutil::removeExtension(filePath) + " - list.txt", listingFile);
}
/**
 * Executes pass 2 of the assembly process and returns the object code.
 * @param intermediateFileName The name of the intermediate file.
 * @param lines A vector containing all the lines in the program.
 * @param programName The name of the assembly program.
 * @param programStart The starting address of the assembly program.
 * @param locCtr The final value of the location counter.
 * @param symbolTable The symbol table.
 * @param firstExecutableAddress The address of the first executable instruction in the assembly program.
 * @return The object file.
 */
std::string executePass2(std::string filePath, std::vector<Line> &lines, std::string programName,
                  int programStart, int locCtr, SymbolTable symbolTable, int firstExecutableAddress) {
    const int MAX_LINE_LENGTH = 30;
    std::ostringstream objCodeStream;
    int initLocCtr = programStart;
    initHeader(objCodeStream, programName, initLocCtr, locCtr - initLocCtr);
    bool startNewLine = false;
    std::string curRecord;
    objCodeStream << "T";
    strutil::addHex(objCodeStream, initLocCtr, 6);
    std::ostringstream errors;
    for (int i = 1 ; i < lines.size() ; i++) {
        Line line = lines[i];
        if (line.error) {
            errors << *line.error;
            errors << ". At line: " << i + 1 << std::endl;
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
                if (numutil::Hexadecimal::isHexLiteral(line.operand)) {
                    std::string hexLiteral = numutil::Hexadecimal::parseHexadecimalLiteral(line.operand);
                    for (int j = 0; j < hexLiteral.length(); j += numHalfBytes) {
                        locCtr += numHalfBytes;
                        std::string seg = hexLiteral.substr(j, numHalfBytes);
                        if (locCtr > initLocCtr + MAX_LINE_LENGTH) {
                            curRecord += lineObjectCode.str();
                            lines[i].objCode += lineObjectCode.str();
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
                            lines[i].objCode += lineObjectCode.str();
                            initRecord(objCodeStream, initLocCtr, curRecord.length() / 2, curRecord, locCtr);
                            lineObjectCode.str("");
                            addHexBytes(lineObjectCode, seg, numBytes);
                        }
                    }
                } else if (strutil::toUpper(line.operation) == "WORD") {
                    try {
                        if (strutil::isValidInteger(line.operand)) {
                            strutil::addHex(lineObjectCode, std::stoi(line.operand), 6);
                        } else if (strutil::isValidHexadecimal(line.operand)) {
                            strutil::addHex(lineObjectCode, std::stoi(line.operand, 0, 16), 6);
                        } else {
                            errors << "ERROR: Operand \"" << line.operand;
                            errors << "\" is not a valid operand. At line: " << i + 1 << std::endl;
                        }
                    } catch (std::invalid_argument ex) {
                        errors << "ERROR: Operand \"" << line.operand;
                        errors << "\" is not a valid operand. At line: " << i + 1 << std::endl;
                    } catch (std::out_of_range ex) {
                        errors << "ERROR: Operand \"" << line.operand;
                        errors << "\" is not a valid operand. At line: " << i + 1 << std::endl;
                    }
                } else {
                    errors << "ERROR: Operand \"" << line.operand;
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
                        errors << "ERROR: Symbol \"" << line.operand;
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
        lines[i].objCode += lineObjectCode.str();
        curRecord += lineObjectCode.str();
    }
    if (!curRecord.empty()) {
        strutil::addHex(objCodeStream, curRecord.length() / 2, 2);
        objCodeStream << curRecord;
    } else {
        throw std::invalid_argument(errors.str());
    }
    objCodeStream << "\n";
    addEndRecord(objCodeStream, firstExecutableAddress);
    writeListingFile(filePath, lines);
    if (errors.str().empty()) {
        return objCodeStream.str();
    } else {
        throw std::invalid_argument(errors.str());
    }
}
/**
 * Takes an assembly file and generates its object code.
 * @param filePath The path of the assembly file.
 * @param options The assembler options.
 */
void Assembler::execute(std::string filePath, std::map<std::string, std::string> options) {
    int firstExecutableAddress = locCtr = 0;
    int programStart = 0;
    int literalLabelCounter = 0;
    std::string programName = "";
    std::vector<Line> lines;
    SymbolTable symbolTable;
    LiteralTable literalTable;
    std::string intermediateFile = executePass1(filePath, options, lines, programName, programStart,
                                                locCtr, literalTable ,symbolTable, firstExecutableAddress,
                                                literalLabelCounter);
    std::cout << "Intermediate File:" << std::endl;
    std::cout << intermediateFile;
    writeFile(fileutil::removeExtension(filePath) + " - inter.txt", intermediateFile);
    std::string objFile = executePass2(filePath, lines, programName,
                                       programStart, locCtr, symbolTable, firstExecutableAddress);
    writeFile(fileutil::removeExtension(filePath) + ".obj", objFile);
    std::cout << "Assembled Successfully!" << std::endl;
    std::cout << "Object File:" << std::endl;
    std::cout << objFile;
}


