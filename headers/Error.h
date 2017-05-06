//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#ifndef SIC_XE_ASSEMBLER_ERROR_H
#define SIC_XE_ASSEMBLER_ERROR_H

#include <iosfwd>

class Error {
public:
    Error();
    Error(ErrorType errorType, std::string errorCase);
    ~Error();
    ErrorType errorType;
    std::string errorCause;
    InstructionFormat instructionFormat;

private:
    friend std::ostream& operator<<(std::ostream& stream, const Error& error);
};

#endif //SIC_XE_ASSEMBLER_ERROR_H
