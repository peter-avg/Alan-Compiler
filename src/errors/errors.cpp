#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>

#include "errors.hpp"
#include "../colors/colors.hpp"

extern const char *filename;
extern int line_number;

std::string version = "1.0.0";


void ClearScreen() {
    sleep(1);
    system("clear");
}


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

void newSemanticError(int code, std::string &message_1, std::string &message_2) {
    message_2 = "";
    switch (code){
        case entryExistsError_c:
            message_1 = "Entry already exists";
            break;
        case variableExistsError_c:
            message_1 = "Variable ";
            message_2 = " already exists";
            break;
        case variableNotFoundError_c:
            message_1 = "Variable ";
            message_2 = " not found";
            break;
        case parameterExistsError_c:
            message_1 = "Parameter "; 
            message_2 = " already exists in function ";
            break;
        case functionExistsError_c:
            message_1 = "Function ";
            message_2 = " already exists";
            break;
        case nonVoidFunctionVoidReturn:
            message_1 = "Non-Void function ";
            message_2 = " does not return anything";
        case voidFunctionWrongReturnError_c:
            message_1 = "Void function "; 
            message_2 = " has a return type";
            break;
        case functionRequiresMoreReturnsError_c:
            message_1 = "Non-Void function ";
            message_2 = " requires one or more return statements";
            break;
        case conditionTypeError_c:
            message_1 = "Condition is not of byte type";
            break;
        case expressionsDiffTypeError_c:
            message_1 = "Expressions ";
            message_2 = " have different types";
            break;
        case operandMismatchType_c: 
            message_1 = "Operands of"; 
            message_2 = " condition have different types";
            break;
        case returnTypeMismatchError_c:
            message_1 = "Function ";
            message_2 = " return-type mismatch";
            break;
        case BinOpTypeMismatchError_c:
            message_1 = "Binary operation expressions don't have the same type";
            break;
        case arrayindexTypeError_c:
            message_1 = "Index of array ";
            message_2 = " must be of type int";
            break;
        case nosuchfunctionError_c:
            message_1 = "Function ";
            message_2 = " not found";
            break;
        case idnotfunctionError_c:
            message_1 = "Entry ";
            message_2 = " is not a function";
            break;
        case notenoughparamsError_c:
            message_1 = "Call to function ";
            message_2 = " requires more arguments";
            break;
        case toomanyparamsError_c:
            message_1 = "Call to function ";
            message_2 = " contains too many arguments";
            break;
        case argumentTypeMismatchError_c:
            message_1 = "Type of argument ";
            message_2 = " does not match type of parameter ";
            break;
        case nonArrayWrongIndexing_c:
            message_1 = "Non-array variable ";
            message_2 = " cannot be indexed";
            break;
        case uninitializedVariableWarning_c:
            message_1 = "Variable ";
            message_2 = " may be used uninitialized";
            break;
    }
}

std::string newFileError(int code) {
    std::string message;

    switch (code) {
        case nofileError_c:
            message = "File not found error";
            break;
        case badfileError_c:
            message = "Bad file error";
            break;
        case segfaultError_c:
            message = "Segmentation fault error";
            break;
    }

    return message;
}

std::string newLLVMError(int code) {
    std::string message;

    switch (code) {
        case EmptyScopeError_c:
            message = "The scope you are trying to close is empty";
            break;
        case VariableNotFoundError_c:
            message = "Variable not found";
            break;
        case FunctionNotFoundError_c:
            message = "Function not found";
            break;
        case BadIRError_c:
            message = "Bad IR";
            break;
    }

    return message;
}

void RaiseTokenError(int code, char token, int ascii) { 
    std::string message = newTokenError(code);
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
    colors::Font reset = {colors::Color::RESET,colors::Style::NORMAL};
    std::cout << green_bold << "{File: " 
              << filename << "}::" << "{Line: " << line_number 
              << "}" << red_normal << "\nTokenError: " 
              << white_normal << message << ": '" << token
              << "' (ASCII: " << ascii << ")" << std::endl << reset;

    exit(EXIT_FAILURE);
}

void RaiseParserError(const char* message, int line_number) {
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
    colors::Font reset = {colors::Color::RESET,colors::Style::NORMAL};
    std::cout << green_bold << "{File: " 
              << filename << "}::" << "{Line: " << line_number 
              << "}" << red_normal << "\nParserError: " 
              << white_normal << message << std::endl << reset;
    exit(EXIT_FAILURE);
}

void RaiseTypeError(int code) {
    std::string message = newTypeError(code);
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BLINK};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
    colors::Font reset = {colors::Color::RESET,colors::Style::HIDDEN};
    std::cout << green_bold << "{File: " 
              << filename << "}::" << "{Line: " << line_number 
              << "}" << red_normal << "\nTypeError: " 
              << white_normal << message << std::endl << reset;
    exit(EXIT_FAILURE);
}

void RaiseSemanticError(int code, Fatality type, std::string id_1, std::string id_2) {
    std::string message_1="";
    std::string message_2="";
    newSemanticError(code, message_1, message_2);
    if (type == FATAL) {
        colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
        colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
        colors::Font white_faded = {colors::Color::WHITE, colors::Style::UNDERLINED};
        colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
        colors::Font reset = {colors::Color::RESET,colors::Style::HIDDEN};
        std::cout << green_bold << "{File: " 
                  << filename << "}::" << "{Line: " << line_number 
                  << "}" << red_normal << "\n SemanticError: " 
                  << white_normal << message_1 << white_faded << id_1 
                  << white_normal << message_2 << id_2 << std::endl << reset;

        exit(EXIT_FAILURE);
    }
    else if (type == WARNING) {
        colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
        colors::Font magenta_normal = {colors::Color::MAGENTA,colors::Style::NORMAL};
        colors::Font white_faded = {colors::Color::WHITE, colors::Style::UNDERLINED};
        colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
        colors::Font reset = {colors::Color::RESET,colors::Style::HIDDEN};
        std::cout << green_bold << "{File: " 
                  << filename << "}::" << "{Line: " << line_number 
                  << "}" << magenta_normal << "\n SemanticWarning: " 
                  << white_normal << message_1 << white_faded << id_1 
                  << white_normal << message_2 << id_2 << std::endl << reset;
    }
}

void RaiseFileError(int code) {
    std::string message = newFileError(code);
    colors::Font red_normal = {colors::Color::RED,colors::Style::BOLD};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
    colors::Font reset = {colors::Color::RESET,colors::Style::HIDDEN};
    std::cout << red_normal << "\nFileError: " 
              << white_normal << message << std::endl << reset;
    exit(EXIT_FAILURE);
}

void RaiseLLVMError(int code) {
    std::string message = newLLVMError(code);
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
    colors::Font reset = {colors::Color::RESET,colors::Style::HIDDEN};
    std::cout << green_bold << "{File: " 
              << filename << "}::" << "{Line: " << line_number 
              << "}" << red_normal << "\n LLVMError: " 
              << white_normal << message << std::endl << reset;
    exit(EXIT_FAILURE);
}

