%{
#define T_eof 0
//#define YYSTYPE union yylval
#include "../types/types.hpp"
#include "../ast/ast.hpp"
//#include "../parser/parser.tab.h"
#include "../parser/parser.hpp"
#include "../correcting/correcting.hpp"
#include "../lexer/lexer.h"
#include "../errors/errors.hpp"
#include <cstdlib>
#include <cstring>

int line_number = 1;
int nested_comments = 0;
%}

L [a-z_A-Z]
D [0-9]
W [ \t\r]
E [ntr0\'\"\\]
N [a-fA-F0-9]

%x COMMENT
%option noyywrap

%%
"Print"     { return T_print; }
"byte"      { return T_byte; }
"else"      { return T_else; }
"false"     { return T_false; }
"if"        { return T_if; }
"int"       { return T_int; }
"proc"      { return T_proc; }
"reference" { return T_reference; }
"return"    { return T_return; }
"while"     { return T_while; }
"true"      { return T_true; }


[()\[\]{}=+\-*/\%!&\|<>,:;]             { return yytext[0];}
"=="                                    { return T_equal;}
"!="                                    { return T_notequal;}
"<="                                    { return T_lessequal;}
">="                                    { return T_greaterequal;}

{L}({L}|{D})*       {   yylval.sval = strdup(yytext);
                        return T_id; }
{D}+                {   yylval.ival = atoi(yytext); 
                        return T_const; }

\"(\\.|[^\\"])*\"                    {   std::string current = correctString(yytext+1);
                                    yylval.sval = strdup(current.c_str());
                                    return T_string; }
\'({L}|[ ]|\\(x{N}{N}|{E}))\'      {    int next = 0;
                                    yylval.cval =  correctChars(yytext+1, next); return T_char; }

\-\-.*\n            { ++line_number; }
"(*"                { BEGIN(COMMENT); }
<COMMENT>"*)"       { if (nested_comments == 0) BEGIN(INITIAL); else nested_comments--; }
<COMMENT>"(*"       { nested_comments++; }
<COMMENT>\n         { ++line_number; }
<COMMENT>"*"+[^)\n] { /* ignore alone '*' */ }
<COMMENT>"("+[^(*\n] { /* ignore alone '(' that are not followed by '*' */}
<COMMENT>[^(*\n]+   { /* ignore any number of symbols that's not '\n' or '(*' */}

{W}+                { /* ignore whitespace */ }
\n                  { ++line_number; }
.                   { RaiseTokenError(invalidTokenError_c, yytext[0], yytext[0]); }

%%

void yyerror(const char *s) {
    RaiseParserError(s, line_number);
}

/*
int main() {
    int token;
    do {
        token = yylex();
        printf("token=%d, lexeme=\"%s\"\n", token, yytext);
    } while (token != T_eof);
}*/
