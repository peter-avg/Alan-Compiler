%{

#include <iostream>
#include <cstdlib>
#include <string>
#include "../lexer/lexer.h"
#include "../ast/ast.hpp"


#define YYDEBUG 1
extern FILE* yyin;
extern int line_number;
//extern int yylex();
%}

%union {
    ASTPtr *a;
    ASTList *al;
    int ival;
    char cval;
    char *sval;
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

%left '!'
%left '&'
%left '|'
%nonassoc '<' '>' "==" "!=" "<=" ">="

%left '+' '-'
%left '*' '/' '%'

%nonassoc NOELSE
%nonassoc "else"
 


%type <a> data_type
%type <a> type
%type <a> r_type
%type <a> cond
%type <a> l_value
%type <a> expr
%type <al> expr_list
%type <a> func_call
%type <a> stmt
%type <al> stmt_list
%type <a> compound_stmt
%type <a> var_def
%type <a> local_def
%type <al> local_def_list
%type <al> fpar_list
%type <a> fpar_def
%type <a> func_def
%type <a> program



%start program

%%

data_type
    : T_int     { $$ = new ASTPtr(std::make_shared<Int>());  }
    | T_byte    { $$ = new ASTPtr(std::make_shared<Byte>()); }
    ;

type
    : data_type '[' ']' { $$ = new ASTPtr(std::make_shared<Array>(*$1)); }
    | data_type         { $$ = $1;                                      }
    ;

r_type
    : data_type         { $$ = $1;                                   }
    | "proc"            { $$ = new ASTPtr(std::make_shared<Type>()); } 
    ;

cond
    : "true"            { $$ = new ASTPtr(std::make_shared<Cond>("true"));       }
    | "false"           { $$ = new ASTPtr(std::make_shared<Cond>("false"));      }
    | '(' cond ')'      { $$ = $2;                                              }
    | '!' cond          { $$ = $2;                                              }
    | expr '<' expr     { $$ = new ASTPtr(std::make_shared<Cond>("<", *$1, *$3));  }
    | expr '>' expr     { $$ = new ASTPtr(std::make_shared<Cond>(">", *$1, *$3));  }
    | expr "==" expr    { $$ = new ASTPtr(std::make_shared<Cond>("==", *$1, *$3)); }
    | expr "!=" expr    { $$ = new ASTPtr(std::make_shared<Cond>("!=", *$1, *$3)); }
    | expr "<=" expr    { $$ = new ASTPtr(std::make_shared<Cond>("<=", *$1, *$3)); }
    | expr ">=" expr    { $$ = new ASTPtr(std::make_shared<Cond>(">=", *$1, *$3)); }
    | cond '&' cond     { $$ = new ASTPtr(std::make_shared<Cond>("&", *$1, *$3));  }
    | cond '|' cond     { $$ = new ASTPtr(std::make_shared<Cond>("|", *$1, *$3));  }
    ;

l_value
    : T_string          { $$ = new ASTPtr(std::make_shared<String>($1));       }
    | T_id '[' expr ']' { $$ = new ASTPtr(std::make_shared<LValue>($1, *$3));   }
    | T_id              { $$ = new ASTPtr(std::make_shared<LValue>($1));       }
    ;

expr
    : T_char            { $$ = new ASTPtr(std::make_shared<Char>($1));           }
    | T_const           { $$ = new ASTPtr(std::make_shared<Const>($1));          } 
    | l_value           { $$ = $1;                                               }
    | '(' expr ')'      { $$ = $2;                                               }
    | func_call         { $$ = $1;                                               }
    | '+' expr          { $$ = new ASTPtr(std::make_shared<BinOp>('+', *$2));     }
    | '-' expr          { $$ = new ASTPtr(std::make_shared<BinOp>('-', *$2));     }
    | expr '+' expr     { $$ = new ASTPtr(std::make_shared<BinOp>('+', *$1, *$3)); }
    | expr '-' expr     { $$ = new ASTPtr(std::make_shared<BinOp>('-', *$1, *$3)); }
    | expr '*' expr     { $$ = new ASTPtr(std::make_shared<BinOp>('*', *$1, *$3)); }
    | expr '/' expr     { $$ = new ASTPtr(std::make_shared<BinOp>('/', *$1, *$3)); }
    | expr '%' expr     { $$ = new ASTPtr(std::make_shared<BinOp>('%', *$1, *$3)); }
    ;


expr_list 
    :                      { $$ = new ASTList();                    }
    | expr_list ',' expr   { $1->push_back(*$3); $$ = $1;            }
    | expr                 { $$ = new ASTList(); $$->push_back(*$1); }
    ;

func_call
    : T_id '(' expr_list ')' { $$ = new ASTPtr(std::make_shared<Call>($1, *$3)); }
    ;

stmt
    : ';'                                   { $$ = nullptr;            }
    | l_value '=' expr ';'                  { $$ = new ASTPtr(std::make_shared<Assign>(*$1, *$3)); }
    | compound_stmt                         { $$ = $1;                 }
    | func_call ';'                         { $$ = $1;                 }
    | "if" '(' cond ')' stmt                { $$ = new ASTPtr(std::make_shared<If>(*$3, *$5));     }
    | "if" '(' cond ')' stmt "else" stmt    { $$ = new ASTPtr(std::make_shared<If>(*$3, *$5, *$7)); }
    | "while" '(' cond ')' stmt             { $$ = new ASTPtr(std::make_shared<While>(*$3, *$5));  }
    | "return" expr ';'                     { $$ = new ASTPtr(std::make_shared<Return>(*$2));     }
    ;

stmt_list
    :                   { $$ = new ASTList();      }
    | stmt_list stmt    { $1->push_back(*$2); $$ = $1; }
    ;

compound_stmt
    : '{' stmt_list '}' { $$ = new ASTPtr(std::make_shared<Block>()); }
    ;


var_def
    : T_id ':' data_type';'                  { $$ = new ASTPtr(std::make_shared<Var>($1, *$3));     }
    | T_id ':' data_type '[' T_const ']' ';' { $$ = new ASTPtr(std::make_shared<Var>($1, *$3, $5)); }
    ;

local_def
    : func_def  { $$ = $1; }
    | var_def   { $$ = $1; }
    ;

local_def_list
    :                          { $$ = new ASTList(); }
    | local_def_list local_def { $1->push_back(*$2); $$ = $1;                     }
    ;



fpar_def
    : T_id ':' "reference" type { $$ = new ASTPtr(std::make_shared<Param>($1, "reference", *$4)); }
    | T_id ':' type             { $$ = new ASTPtr(std::make_shared<Param>($1, "value" , *$3));    }
    ;

fpar_list
    :                        { $$ = new ASTList(); }
    | fpar_list ',' fpar_def { $1->push_back(*$3); $$ = $1;                     }
    | fpar_def               { $$ = new ASTList(); $$->push_back(*$1); }
    ;

func_def
    : T_id '(' fpar_list ')' ':' r_type local_def_list compound_stmt 
    { std::cout << *$6 << std::endl;
    $$ = new ASTPtr(std::make_shared<Func>($1, *$3, *$6, *$7, *$8)); }
    ;

program
: func_def { std::cout << "AST: " << *(*$1) << std::endl;
                if($1 == nullptr) std::cout << "shit" << std::endl;
                $$ = $1;}
    ;

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char *filename = argv[1];
    FILE *inputFile = fopen(filename, "r");

    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return 1;
    }

    yyin = inputFile;  // Set yyin to read from the provided file

    int res = yyparse();  // Use the generated parser
    fclose(inputFile);   // Close the file when done

    if (res == 0) {
        std::cout << "Parsing successful" << std::endl;
        return 0;
    }

    std::cerr << "Parsing failed at line " << line_number << std::endl;
    return 1;
}

//int main(int argc, char *argv[]) {
//    
//    yydebug = 1;
//
//    int res = yyparse();
//    if (res == 0) {
//        std::cout << "Parsing successful" << std::endl;
//        exit(EXIT_SUCCESS);
//    }
//
//    std::cout << "Parsing failed at " << line_number << std::endl;
//    exit(EXIT_FAILURE);
//}
