/**
 * @file Line.h
 * A file containing the declaration of the Error class.
 */

#ifndef SIC_XE_ASSEMBLER_ERROR_H
#define SIC_XE_ASSEMBLER_ERROR_H

#include "enums.h"
#include <iostream>
#include <string>

/**
 * The error class.
 */
class Error {
public:
    /**
     * Constructs a new Error.
     */
    Error();

    /**
     * Constructs a new Error given the type and the cause.
     * @param errorType The type of the error.
     * @param errorCase The cause of the error.
     */
    Error(ErrorType errorType, const std::string &errorCase);

    /**
     * Destructs an Error.
     */
    ~Error();

    /**
     * The type of the error.
     */
    ErrorType errorType;
    /**
     * The cause of the error.
     */
    std::string errorCause;

private:
    /**
     * The definition of the "<<" operator for the types Error and std::ostream.
     * @param stream The output stream.
     * @param error The Error object.
     * @return The output stream after the operation.
     */
    friend std::ostream &operator<<(std::ostream &stream, const Error &error);
};

#endif //SIC_XE_ASSEMBLER_ERROR_H
