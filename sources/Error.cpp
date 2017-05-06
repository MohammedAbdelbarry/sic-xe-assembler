//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#include <iomanip>
#include "../headers/enums.h"
#include "../headers/Error.h"
const std::string errorMessages[] = {"Invalid label ", "Unsupported operation ", "Duplicate start ",
                       "Invalid operand ", "Invalid format ", "Comment size shouldn't be greater than 30, found "};
const std::string DOUBLE_QUOTE = "\"";


Error::Error() {

}

Error::Error(ErrorType errorType, std::string errorCause) {
    this->errorType = errorType;
    this->errorCause = errorCause;
}

Error::~Error() {

}

std::ostream &operator<<(std::ostream &stream, const Error &error) {
    std::string errorString= "ERROR: ";
    stream << errorString;
    stream << errorMessages[error.errorType];
    stream << DOUBLE_QUOTE << error.errorCause << DOUBLE_QUOTE;
}



