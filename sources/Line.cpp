//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <string>
#include <iostream>
#include <iomanip>
#include "../headers/enums.h"
#include "../headers/Error.h"
#include "../headers/Line.h"


Line::Line() {

}

Line::Line(std::string label, std::string operation, std::string operand, std::string comment) {
    this->label = label;
    this->operand = operand;
    this->operation = operation;
    this->comment = comment;
    this->error = nullptr;
    this->lineType = LineType::ASSEMBLY_STATEMENT;
}

Line::Line(std::string comment) {
    this->comment = comment;
    this->error = nullptr;
    this->lineType = LineType::COMMENT;
}

std::ostream& operator<<(std::ostream& stream, const Line& line) {
    stream << std::hex << std::uppercase << line.locCtr << "\t";
    stream << line.label << "\t" << line.operation << "\t"
           << line.operand;
    if (line.isIndexed) {
        stream << ",X";
    }
    stream << "\t" << line.comment;
}

Line::~Line() {
//    if (error != nullptr)
//        delete error;
}

LineType Line::getLineType() {
    return this->lineType;
}





