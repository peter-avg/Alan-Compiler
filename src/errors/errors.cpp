#include <stdlib.h>
#include <string>

#include "errors.hpp"
#include "../colors/colors.hpp"

extern std::string file_namen;
extern int line_number;

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

std::string newSemanticError(int code) {
    std::string message;

    switch (code){
        case entryExistsError_c:
            message = "Entry already exists error";
            break;
        case variableExistsError_c:
            message = "Variable already exists error";
            break;
        case variableNotFoundError_c:
            message = "Variable not found error";
            break;
        case parameterExistsError_c:
            message = "Parameter already exists error";
            break;
        case functionExistsError_c:
            message = "Function already exists error";
            break;
        case voidFunctionWrongReturnError_c:
            message = "Void function wrong return error";
            break;
        case conditionTypeError_c:
            message = "Condition not byte type";
            break;
        case expressionsDiffTypeError_c:
            message = "Expressions have different types";
            break;
        case returnTypeMismatchError_c:
            message = "Function Return type mismatch";
            break;
        case BinOpTypeMismatchError_c:
            message = "Binary operation expressions don't have the same type";
            break;
        case arrayindexTypeError_c:
            message = "Index of array must be of type int";
            break;
    }

    return message;
}

void RaiseTokenError(int code, char token, int ascii) { 
    std::string message = newTokenError(code);
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
    std::cout << green_bold << "{File: " 
              << file_name << "}::" << "{Line: " << line_number 
              << "}" << red_normal << "\nTokenError: " 
              << white_normal << message << ": '" << token << "' (ASCII: " << ascii << ")" << std::endl;

    exit(EXIT_FAILURE);
}

void RaiseTypeError(int code) {
    std::string message = newTypeError(code);
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BLINK};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
    std::cout << green_bold << "{File: " 
              << file_name << "}::" << "{Line: " << line_number 
              << "}" << red_normal << "\nTypeError: " 
              << white_normal << message << std::endl;
    exit(EXIT_FAILURE);
}

void RaiseSemanticError(int code, Fatality type) {
    std::string message = newSemanticError(code);
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
    std::cout << green_bold << "{File: " 
              << file_name << "}::" << "{Line: " << line_number 
              << "}" << red_normal << "\n SemanticError: " 
              << white_normal << message << std::endl;

    if (type == FATAL) {
        exit(EXIT_FAILURE);
    }
}
