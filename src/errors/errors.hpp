#ifndef __ERRORS_HPP__
#define __ERRORS_HPP__

#include <string>

extern int line_number;
extern std::string file_name;

typedef enum {
    FATAL,
    WARNING,
    INFO,
} Fatality;

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

typedef enum {
    entryExistsError_c,
    variableExistsError_c,
    variableNotFoundError_c,
    parameterExistsError_c,
    functionExistsError_c,
    voidFunctionWrongReturnError_c,
    conditionTypeError_c,
    expressionsDiffTypeError_c,
    returnTypeMismatchError_c,
    BinOpTypeMismatchError_c,
    arrayindexTypeError_c,
} SemanticErrorCodes;

std::string newTokenError(int code);
std::string newTypeError(int code);
std::string newSemanticError(int code);

void RaiseTypeError(int code);
void RaiseTokenError(int code, char token, int ascii);
void RaiseSemanticError(int code, Fatality fatality);

#endif // __ERRORS_HPP__
