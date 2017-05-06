//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#include <iomanip>
#include "../headers/enums.h"
#include "../headers/Error.h"

const std::string invalidLabel = "Invalid label ";
const std::string unsupportedOperation = "Unsupported operation ";
const std::string duplicateStart = "Duplicate start ";
const std::string invalidOperand = "Invalid Operand ";
const std::string invalidFormat = "Invalid Format ";
//TODO assuming that bars will concatenate "line" and its number.
const std::string extraCharacters = "Extra Character At End of ";

Error::Error(ErrorType errorType, std::string errorCause) {
    this->errorType = errorType;
    this->errorCause = errorCause;
}

Error::Error(ErrorType errorType, InstructionFormat instructionFormat) {
    this->errorType = errorType;
    this->errorCause = errorCause;
}

Error::~Error() {

}

std::ostream &operator<<(std::ostream &stream, const Error &error) {
    //TODO Check this statement below for these nasty compiler error "God bless rms"
    std::string errorString= "ERROR: ";
    stream << errorString;
    switch(error.errorType) {
        case ErrorType::INVALID_LABEL:
            stream << invalidLabel << error.errorCause;
            break;
        case ErrorType::INVALID_OPERAND:
            stream << invalidOperand << error.errorCause;
            break;
        case ErrorType::EXTRA_CHARACTERS_AT_EOL:
            stream << extraCharacters;
            break;
        case ErrorType::UNSUPPORTED_OPERATION:
            stream << unsupportedOperation << error.errorCause;
            break;
        case ErrorType::DUPLICATE_START:
            stream << duplicateStart << error.errorCause;
            break;
        case ErrorType::INVALID_FORMAT:
            stream << invalidFormat << error.errorCause;
            break;
        default:
            break;
    }
}

