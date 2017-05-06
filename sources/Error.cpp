//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#include <iomanip>
#include "../headers/enums.h"
#include "../headers/Error.h"




const std::string invalidInput = "Invalid label";
const std::string unsupportedOperation = "Unsupported operation";
const std::string duplicateStart = "Duplicate start";
const std::string undefinedOperand = "Undefined Operand";
const std::string invalidFormat = "Invalid Format";
const std::string extraCharacters = "Extra Character At End of Line";

Error::Error() {

}

Error::Error(ErrorMessage errorMessage) {
    this->errorMessage = errorMessage;
}

Error::~Error() {

}

std::ostream &operator<<(std::ostream &stream, const Error &error) {
    //TODO Check this statement below for these nasty compiler error "God bless rms"
    std::string errorString= "ERROR: ";
    stream << errorString;
    switch(error.errorMessage) {
        case ErrorMessage::INVALID_LABEL:
            stream << invalidInput;
            break;
        case ErrorMessage::UNDEFINED_OPERAND:
            stream << undefinedOperand;
            break;
        case ErrorMessage::EXTRA_CHARACTERS_AT_EOL:
            stream << extraCharacters;
            break;
        case ErrorMessage::UNSUPPORTED_OPERATION:
            stream << unsupportedOperation;
            break;
        case ErrorMessage::DUPLICATE_START:
            stream << duplicateStart;
            break;
        case ErrorMessage::INVALID_FORMAT:
            stream << invalidFormat;
            break;
        default:
            break;
    }
}

