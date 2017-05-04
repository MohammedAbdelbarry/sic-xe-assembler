//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <string>
#include "../headers/enums.h"
#include "../headers/Line.h"

Line::Line(std::string label, std::string operation, std::string operand) {
    this->label = label;
    this->operand = operand;
    this->operation = operation;
    this->error = nullptr;
}
