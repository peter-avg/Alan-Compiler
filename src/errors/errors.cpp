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
