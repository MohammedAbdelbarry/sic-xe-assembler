//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#ifndef SIC_XE_ASSEMBLER_ERROR_H
#define SIC_XE_ASSEMBLER_ERROR_H

#include <iosfwd>

class Error {

public:
    Error();
    Error(ErrorMessage errorMessage);
    ~Error();
    ErrorMessage errorMessage;

private:
    friend std::ostream& operator<<(std::ostream& stream, const Error& error);
};

#endif //SIC_XE_ASSEMBLER_ERROR_H
