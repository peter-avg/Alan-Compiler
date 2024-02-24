#include <stdlib.h>
#include <string>

#include "errors.hpp"
#include "../colors/colors.hpp"

std::string newTokenError(int code) {
    
    std::string message;

    switch(code) {
        case invalidTokenError_c:
            message = "Invalid token error";
            break;
    }

    return message;

}

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

void RaiseTokenError(int code) { 
    std::string message = newTokenError(code);
    std::cout << colors::Color::GREEN << "{File: " 
              << file_name << "}::" << "{Line: " << line_number 
              << "}" << colors::Color::RED << "\nTokenError: " 
              << colors::Color::WHITE << message << std::endl;
    exit(EXIT_FAILURE);
}

void RaiseTypeError(int code) {
    std::string message = newTypeError(code);
    std::cout << colors::Color::GREEN << "{File: " 
              << file_name << "}::" << "{Line: " << line_number 
              << "}" << colors::Color::RED << "\nTypeError: " 
              << colors::Color::WHITE << message << std::endl;
    exit(EXIT_FAILURE);
}
