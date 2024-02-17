#include <stdlib.h>
#include <string>

#include "errors.hpp"
#include "../colors/colors.hpp"

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
        case integerOverflowError_c:
            message = "Integer overflow error";
            break;
        case byteOverflowError_c:
            message = "Byte overflow error";
            break;
    }

    return message;
}

void RaiseTypeError(int code) {
    std::string message = newTypeError(code);
    std::cout << colors::Color::RED << "TypeError: " 
              << colors::Color::RESET << message << std::endl;
    exit(EXIT_FAILURE);
}

