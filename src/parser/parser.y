%{

#include <iostream>
#include <cstdlib>
#include <string>
#include "../lexer/lexer.h"

#define YYDEBUG 1

extern int line_number;

%}

%union {
    int ival;
    char cval;
    std::string sval;
}

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

%token<sval> T_id
%token<ival> T_const
%token<cval> T_char
%token<sval> T_string

%left<binop> '&'
%left<binop> '|'
%nonassoc<binop> '<' '>' "==" "!=" "<=" ">="

%left<binop> '+' '-'
%left<binop> '*' '/' '%'

%nonassoc NOELSE
%nonassoc "else"

%start program

%%

data_type
    : "int"     { $$ = new Int();  }
    | "byte"    { $$ = new Byte(); }
    ;

type
    : data_type '[' ']' { $$ = new Array($1); }
    | data_type         { $$ = $1;            }
    ;

r_type
    : data_type         { $$ = new Return($1);       }
    | "proc"            { $$ = new Return(nullptr);  }
    ;

cond
    : "true"            { $$ = new Condition("true", nullptr, nullptr);  }
    | "false"           { $$ = new Condition("false", nullptr, nullptr); }
    | '(' cond ')'      { $$ = $2;                                       }
    | '!' cond          { $$ = new Condition("not", nullptr, $2);        }
    | expr '<' expr     { $$ = new Condition("<", $1, $3);               }
    | expr '>' expr     { $$ = new Condition(">", $1, $3);               }
    | expr "==" expr    { $$ = new Condition("==", $1, $3);              }
    | expr "!=" expr    { $$ = new Condition("!=", $1, $3);              }
    | expr "<=" expr    { $$ = new Condition("<=", $1, $3);              }
    | expr ">=" expr    { $$ = new Condition(">=", $1, $3);              }
    | cond '&' cond     { $$ = new Condition("and", $1, $3);             }
    | cond '|' cond     { $$ = new Condition("or", $1, $3);              }
    ;

l_value
    : T_string          { }
    | T_id '[' expr ']' { }
    | T_id              { }
    ;

expr
    : T_char            { $$ = new Char($1);                    }       
    | T_const           { $$ = new Const($1);                   }
    | l_value           { $$ = new LValue($1);                  }
    | '(' expr ')'      { $$ = $2;                              }
    | func_call         { $$ = new FunctionCall($1);            }
    | '+' expr          {                                       }
    | '-' expr          {                                       }
    | expr '+' expr     { $$ = new BinaryOperation($1, $2, $3); }
    | expr '-' expr     { $$ = new BinaryOperation($1, $2, $3); }
    | expr '*' expr     { $$ = new BinaryOperation($1, $2, $3); }
    | expr '/' expr     { $$ = new BinaryOperation($1, $2, $3); }
    | expr '%' expr     { $$ = new BinaryOperation($1, $2, $3); }
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
    : ';'                   { }
    | l_value '=' expr ';'  { $$ = new LValue($3); }
    | compound_stmt         { $$ = new Statement($1); }
    | func_call ';'         { }
    | "if" '(' cond ')' stmt %prec NOELSE   { $$ = new If($3,$5,nullptr);    }
    | "if" '(' cond ')' stmt "else" stmt    { $$ = new If($3,$5,$7); }
    | "while" '(' cond ')' stmt             { $$ = new While($3,$5); }
    | "return" expr ';'                     { $$ = new Return($2);   }
    ;

stmt_list               
    :                   { $$ = new Block(); }
    | stmt_list stmt    { $1->append($2); $$ = $1; }
    ;

compound_stmt
    : '{' stmt_list '}' { $$ = new Block(); }
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
    : T_id '(' fpar_list ')' ':' r_type local_def_list compound_stmt { $$ = new Function(); }
    ;

program
    : func_def { std::cout << "AST: " *$1 << std::endl; }
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
