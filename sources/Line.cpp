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
    stream << "Line(" << std::setw(8) << std::left << line.label  << " ";
    stream << std::setw(6) << std::left << line.operation << " ";
    stream << line.operand << ")";
}

Line::~Line() {
//    if (error != nullptr)
//        delete error;
}

LineType Line::getLineType() {
    return this->lineType;
}





