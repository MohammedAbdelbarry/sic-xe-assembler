//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#ifndef SIC_XE_ASSEMBLER_ERROR_H
#define SIC_XE_ASSEMBLER_ERROR_H

class Error {

public:
    Error();
    ~Error();
    Error(ErrorMessage errorMessage);
    ErrorMessage errorMessage;
};

#endif //SIC_XE_ASSEMBLER_ERROR_H
