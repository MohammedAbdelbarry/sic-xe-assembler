/**
 * @file Error.cpp
 * The file containing the implementation of the Error class.
 */
#include "../headers/Error.h"
#include <iomanip>

/**
 * A static array containing the error message
 * corresponding to the type of the error.
 */
const std::string errorMessages[] = {"Invalid label ", "Unsupported operation ", "Duplicate start ",
                                     "Invalid operand ", "Invalid format ",
                                     "Comment size shouldn't be greater than 30, found "};
/**
 * Double quote """.
 */
const std::string DOUBLE_QUOTE = "\"";

Error::Error() {

}

Error::Error(ErrorType errorType, const std::string &errorCause) {
    this->errorType = errorType;
    this->errorCause = errorCause;
}

Error::~Error() {

}

std::ostream &operator<<(std::ostream &stream, const Error &error) {
    std::string errorString = "ERROR: ";
    stream << errorString;
    stream << errorMessages[error.errorType];
    stream << DOUBLE_QUOTE << error.errorCause << DOUBLE_QUOTE;
    return stream;
}



