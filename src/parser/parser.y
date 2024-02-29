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

%token<str> T_id
%token<val> T_const
%token<ch> T_char
%token<str> T_string

%left<op> '&'
%left<op> '|'
%nonassoc<op> '<' '>' "==" "!=" "<=" ">="

%left<op> '+' '-'
%left<op> '*' '/' '%'

%nonassoc NOELSE
%nonassoc "else"


%union {
    Block *block;
    Var *var;
    Array *array;
    Char *chh;
    Const *conn;
    String *string;
    Cond *cond;
    BinOp *op;
    Assign *assign;
    Call *call;
    If *ff;
    While *ww;
    Return *rr;
    Param *param;
    Func *func;
    std::string str;
    int val;
    char ch;
}

%type<block> program stmt_list compound_stmt
%type<var> var_def
%type<array> local_def
%type<array> local_def_list
%type<param> fpar_def
%type<param> fpar_list
%type<func> func_def
%type<cond> cond
%type<op> expr
%type<assign> stmt

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
    : data_type         { $$ = $1;                   }
    | "proc"            { $$ = nullptr;              }
    ;

cond
    : "true"            { $$ = new Cond("true");     }
    | "false"           { $$ = new Cond("false");    }
    | '(' cond ')'      { $$ = $2;                   }
    | '!' cond          { $$ = new Cond($1, $2);     }
    | expr '<' expr     { $$ = new Cond($1, $2, $3); }
    | expr '>' expr     { $$ = new Cond($1, $2, $3); }
    | expr "==" expr    { $$ = new Cond($1, $2, $3); }
    | expr "!=" expr    { $$ = new Cond($1, $2, $3); }
    | expr "<=" expr    { $$ = new Cond($1, $2, $3); }
    | expr ">=" expr    { $$ = new Cond($1, $2, $3); }
    | cond '&' cond     { $$ = new Cond($1, $2, $3); }
    | cond '|' cond     { $$ = new Cond($1, $2, $3); }
    ;

l_value
    : T_string          { $$ = new String($1);    }
    | T_id '[' expr ']' { $$ = new Array($1, $3); }
    | T_id              { $$ = new Var($1);       }
    ;

expr
    : T_char            { $$ = new Char($1);           }
    | T_const           { $$ = new Const($1);          } 
    | l_value           { $$ = $1;                     }
    | '(' expr ')'      { $$ = $2;                     }
    | func_call         { $$ = $1;                     }
    | '+' expr          { $$ = new BinOp('+', $2);     }
    | '-' expr          { $$ = new BinOp('-', $2);     }
    | expr '+' expr     { $$ = new BinOp('+', $1, $3); }
    | expr '-' expr     { $$ = new BinOp('-', $1, $3); }
    | expr '*' expr     { $$ = new BinOp('*', $1, $3); }
    | expr '/' expr     { $$ = new BinOp('/', $1, $3); }
    | expr '%' expr     { $$ = new BinOp('%', $1, $3); }
    ;


expr_list 
    : 
    | expr_list ',' expr   { $1->append($3); $$ = $1; }
    | expr                 { $$ = $1;                 }
    ;

func_call
    : T_id '(' expr_list ')' { $$ = new Call($1, $3); }
    ;

stmt
    : ';'                                   { $$ = nullptr;            }
    | l_value '=' expr ';'                  { $$ = new Assign($1, $3); }
    | compound_stmt                         { $$ = $1;                 }
    | func_call ';'                         { $$ = $1;                 }
    | "if" '(' cond ')' stmt                { $$ = new If($3, $5);     }
    | "if" '(' cond ')' stmt "else" stmt    { $$ = new If($3, $5, $7); }
    | "while" '(' cond ')' stmt             { $$ = new While($3, $5);  }
    | "return" expr ';'                     { $$ = new Return($2);     }
    ;

stmt_list
    :                   { $$ = new Block();        }
    | stmt_list stmt    { $1->append($2); $$ = $1; }
    ;

compound_stmt
    : '{' stmt_list '}' { $$ = new Block($2); }
    ;


var_def
    : T_id ':' data_type';'                  { $$ = new Var($1, $3);     }
    | T_id ':' data_type '[' T_const ']' ';' { $$ = new Var($1, $3, $5); }
    ;

local_def
    : func_def  { $$ = $1; }
    | var_def   { $$ = $1; }
    ;

local_def_list
    : 
    | local_def_list local_def { $1->append($2); $$ = $1; }
    ;



fpar_def
    : T_id ':' "reference" type { $$ = new Param($1, "reference", $4); }
    | T_id ':' type             { $$ = new Param($1, "value" , $4);    }
    ;

fpar_list
    : 
    | fpar_list ',' fpar_def { $1->append($3); $$ = $1; }
    | fpar_def               { $$ = $1;                 }
    ;

func_def
    : T_id '(' fpar_list ')' ':' r_type local_def_list compound_stmt 
    { $$ = new Func($1, $3, $6, $7, $8); }
    ;

program
    : func_def { $$ = $1; }
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
