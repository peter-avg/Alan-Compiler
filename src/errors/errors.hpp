// Errors for Alan Programming Language
// Author: Elisavet Papadopoulou, Avgerinos Petros

#ifndef __ERRORS_HPP__
#define __ERRORS_HPP__

typedef enum {
    stringTypeError_c,
    integerTypeError_c,
    integerOverflowError_c,
    byteOverflowError_c,
    byteTypeError_c,
    charTypeError_c,
} TypeErrorCodes;

typedef struct {
    int code;
    char* message;
} TypeError;

void RaiseTypeError(int code);

#endif // __ERRORS_HPP__
