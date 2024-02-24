// Errors for Alan Programming Language
// Author: Elisavet Papadopoulou, Avgerinos Petros

#ifndef __ERRORS_HPP__
#define __ERRORS_HPP__

#include <string>

extern int line_number;
extern std::string file_name;

typedef enum {
    invalidTokenError_c,
} TokenErrorCodes;

typedef enum {
    stringTypeError_c,
    integerTypeError_c,
    integerOverflowError_c,
    byteOverflowError_c,
    byteTypeError_c,
    charTypeError_c,
} TypeErrorCodes;

std::string newTokenError(int code);
std::string newTypeError(int code);

void RaiseTypeError(int code);
void RaiseTokenError(int code);

#endif // __ERRORS_HPP__
