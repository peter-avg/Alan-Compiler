#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "errors.hpp"

std::string newTypeError(int code) {

    std::string message;

    switch (code){
        case stringTypeError_c:
            message = "String type error";
            break;
        case integerTypeError_c:
            message = "Integer type error";
            break;
        case byteTypeError_c:
            message = "Byte type error";
            break;
        case charTypeError_c:
            message = "Char type error";
            break;
    }

    return message;
}

void RaiseTypeError(int code) {
    std::string message = newTypeError(code);
    printf("%s\n", message.c_str());
    exit(EXIT_FAILURE);
}

