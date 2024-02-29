%{

#include <iostream>
#include <cstdlib>
#include <string>
#include "../lexer/lexer.h"

#define YYDEBUG 1

extern int line_number;

%}

%token T_byte "byte"  
%token T_false "false"
%token T_if "if"
%token T_int "int"
%token T_proc "proc" 
%token T_reference "reference"
%token T_return "return"
%token T_while "while"
%token T_true "true" 
%token T_else "else"
%token T_equal "=="
%token T_notequal "!="
%token T_lessequal "<="
%token T_greaterequal ">=" 

%token T_id
%token T_const
%token T_char
%token T_string

%left '&'
%left '|'
%nonassoc '<' '>' "==" "!=" "<=" ">="

%left '+' '-'
%left '*' '/' '%'

%nonassoc NOELSE
%nonassoc "else"

%start program

%%

data_type
    : "int"     {}
    | "byte"    {}
    ;

type
    : data_type '[' ']' {}
    | data_type         {}
    ;

r_type
    : data_type         {}
    | "proc"            {}
    ;

cond
    : "true"            {}
    | "false"           {}
    | '(' cond ')'      {}
    | '!' cond          {}
    | expr '<' expr     {}
    | expr '>' expr     {}
    | expr "==" expr    {}
    | expr "!=" expr    {}
    | expr "<=" expr    {}
    | expr ">=" expr    {}
    | cond '&' cond     {}
    | cond '|' cond     {}
    ;

l_value
    : T_string          {}
    | T_id '[' expr ']' {}
    | T_id              {}
    ;

expr
    : T_char            {}       
    | T_const           {}
    | l_value           {}
    | '(' expr ')'      {}
    | func_call         {}
    | '+' expr          {}
    | '-' expr          {}
    | expr '+' expr     {}
    | expr '-' expr     {}
    | expr '*' expr     {}
    | expr '/' expr     {}
    | expr '%' expr     {}
    ;


expr_list 
    : 
    | expr_list ',' expr    {}
    | expr                  {}
    ;

func_call
    : T_id '(' expr_list ')' {}
    ;

stmt
    : ';'                   {}
    | l_value '=' expr ';'  {}
    | compound_stmt         {}
    | func_call ';'         {}
    | "if" '(' cond ')' stmt %prec NOELSE   {}
    | "if" '(' cond ')' stmt "else" stmt    {}
    | "while" '(' cond ')' stmt             {}
    | "return" expr ';'                     {}
    ;

stmt_list               
    :                   {}
    | stmt_list stmt    {}
    ;

compound_stmt
    : '{' stmt_list '}' {}
    ;


var_def
    : T_id ':' data_type';' {}
    | T_id ':' data_type '[' T_const ']' ';' {}
    ;

local_def
    : func_def  {}
    | var_def   {}
    ;

local_def_list
    : 
    | local_def_list local_def {}
    ;



fpar_def
    : T_id ':' "reference" type {}
    | T_id ':' type             {}
    ;

fpar_list
    : 
    | fpar_list ',' fpar_def {}
    | fpar_def               {}
    ;

func_def
    : T_id '(' fpar_list ')' ':' r_type local_def_list compound_stmt {}
    ;

program
    : func_def {}
    ;

%%

int main(int argc, char *argv[]) {
    
    yydebug = 1;

    int res = yyparse();
    if (res == 0) {
        std::cout << "Parsing successful" << std::endl;
        exit(EXIT_SUCCESS);
    }

    std::cout << "Parsing failed at " << line_number << std::endl;
    exit(EXIT_FAILURE);
}
