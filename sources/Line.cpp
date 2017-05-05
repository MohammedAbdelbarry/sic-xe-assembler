//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <string>
#include <iostream>
#include "../headers/enums.h"
#include "../headers/Error.h"
#include "../headers/Line.h"


Line::Line() {

}

Line::Line(std::string label, std::string operation, std::string operand) {
    this->label = label;
    this->operand = operand;
    this->operation = operation;
}

std::ostream& operator<<(std::ostream& stream, const Line& line) {
    stream << "Line(" << line.label << "\t" << line.operation << "\t" << line.operand << ")";
}

Line::~Line() {
//    delete error;
}

