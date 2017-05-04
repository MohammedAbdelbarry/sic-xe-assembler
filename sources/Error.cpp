//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#include "../headers/enums.h"
#include "../headers/Error.h"

Error::Error() {

}

Error::Error(ErrorMessage errorMessage) {
    this->errorMessage = errorMessage;
}

Error::~Error() {

}
