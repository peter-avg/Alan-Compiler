%{

#define T_eof 0
#define T_byte 1001  
#define T_false 1002
#define T_if 1003
#define T_int 1004
#define T_proc 1005 
#define T_reference 1006
#define T_return 1007
#define T_while 1008
#define T_true 1009 
#define T_id 1010
#define T_const 1011
#define T_else 1012
#define T_equal 1013
#define T_notequal 1014
#define T_lessequal 1015
#define T_greaterequal 1016 
#define T_string 1017
#define T_enter 1018
#define T_blanks 1019
#define T_character 1020
#define T_linecomment 1021
#define T_multilinecomment 1022
#include "../errors/errors.hpp"


int line_number = 1;
std::string file_name = "hello.txt";

%}

L [a-zA-Z]
D [0-9]
W [ \t\r]

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


[=\+\-\*\/\%\(\)\|\!\<\>\,\:\;\[\]\{\}] { return yytext[0];}
"=="                                    { return T_equal;}
"!="                                    { return T_notequal;}
"<="                                    { return T_lessequal;}
">="                                    { return T_greaterequal;}

{L}({L}|{D})*       { return T_id; }
{D}+                { return T_const; }

\"([^\"])*\"        { return T_string; }
\'([^\'])\'         { return T_character; }

\-\-.*\n            { return T_linecomment; }
\(\*([^\(\*])*\*\)  { return T_multilinecomment;  }
{W}+                { return T_blanks; }
\n                  { ++line_number; }
.                   { RaiseTokenError(invalidTokenError_c); }
%%
/*"(*"            {   int nesting_level = 1;
                    while (nesting_level > 0) {
                        char c = yylex();
                        if (c == T_eof) {
                            RaiseTokenError(invalidTokenError_c);
                            break;
                        }
                        else if (c == "(") {
                            c = yylex();
                            if (c =="*")
                                nesting_level++;
                        }
                        else if (c == "*"){
                            c = yylex();
                            if (c == ")")
                                nesting_level--;
                        }
                    }
                    return T_multilinecomment;
                }
                */


//int yywrap(){
//    return(1);
//}


int main() {

    int token;
    do {
        token = yylex();
        printf("token=%d, lexeme=\"%s\"\n", token, yytext);
    } while (token != T_eof);
}
