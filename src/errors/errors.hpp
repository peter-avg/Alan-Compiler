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
    nofileError_c,
    badfileError_c,
    segfaultError_c,
} ErrorCodes;

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
    functionRequiresMoreReturnsError_c,
    conditionTypeError_c,
    expressionsDiffTypeError_c,
    returnTypeMismatchError_c,
    BinOpTypeMismatchError_c,
    arrayindexTypeError_c,
    nosuchfunctionError_c,
    idnotfunctionError_c,
    nonVoidFunctionVoidReturn,
    notenoughparamsError_c,
    toomanyparamsError_c,
    argumentTypeMismatchError_c,
    operandMismatchType_c,
    nonArrayWrongIndexing_c,
    uninitializedVariableWarning_c,
    entryIsAFunction_c,
} SemanticErrorCodes;

typedef enum {
    EmptyScopeError_c,
    VariableNotFoundError_c,
    FunctionNotFoundError_c,
    BadIRError_c,
} LLVMErrorCodes;

std::string newTokenError(int code);
std::string newTypeError(int code);
void newSemanticError(int code, std::string &message_1, std::string &message_2);
std::string newFileError(int code);
std::string newLLVMError(int code);

void RaiseTypeError(int code);
void RaiseTokenError(int code, char token, int ascii);
void RaiseParserError(const char *message, int line_number);
void RaiseSemanticError(int code, Fatality fatality, std::string id_1 = "", std::string id_2 = "");
void RaiseFileError(int code);
void RaiseLLVMError(int code);
void ClearScreen();

#endif // __ERRORS_HPP__
