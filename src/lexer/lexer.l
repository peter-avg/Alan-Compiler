%{

#define T_eof 0

#include "../ast/ast.hpp"
#include "../parser/parser.hpp"
#include "../lexer/lexer.h"
#include "../errors/errors.hpp"


int line_number = 1;
int nested_comments = 0;
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

\-\-.*\n            { line_number++; }
"(*"                { BEGIN(COMMENT); }
<COMMENT>"*)"       { if (nested_comments == 0) BEGIN(INITIAL); else nested_comments--; }
<COMMENT>"(*"       { nested_comments++; }
<COMMENT>\n         { line_number++; }
<COMMENT>"*"+[^)\n] { /* ignore alone '*' */ }
<COMMENT>"("+[^(*\n] { /* ignore alone '(' that are not followed by '*' */}
<COMMENT>[^(*\n]+   { /* ignore any number of symbols that's not '\n' or '(*' */}

{W}+                { /* ignore whitespace */ }
\n                  { ++line_number; }
.                   { RaiseTokenError(invalidTokenError_c, yytext[0], yytext[0]); }

%%

void yyerror(const char *s) {

}
