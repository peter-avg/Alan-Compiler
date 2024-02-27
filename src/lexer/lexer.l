%{

#define T_eof 0

#include "../parser/parser.hpp"
#include "../lexer/lexer.h"
#include "../errors/errors.hpp"


int line_number = 0;
std::string file_name;

%}

L [a-zA-Z]
D [0-9]
W [ \t\r]

%x COMMENT
%option noyywrap

%%
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

{L}({L}|{D})*       { return T_id; }
{D}+                { return T_const; }

\"([^\"])*\"        { return T_string; }
\'([^\'])\'         { return T_char; }

\-\-.*\n            { /* ignore single line comment */ }
\(\*([^\(\*])*\*\)  { /* ignore multi line comment */}
{W}+                { /* ignore whitespace */ }
\n                  { ++line_number; }
.                   { RaiseTokenError(invalidTokenError_c, yytext[0], yytext[0]); }

%%

void yyerror(const char *s) {

}

