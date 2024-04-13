%{
#include <iostream>
#include <cstdlib>
#include <string>
#include "../lexer/lexer.h"
#include "../errors/errors.hpp"
#include "../types/types.hpp"
#include "../ast/ast.hpp"
#include "../correcting/correcting.hpp"
#include "../symbol/symbol.hpp"
#include <memory>
#define YYDEBUG 1

//%option noyywrap nodefault;
extern FILE* yyin;
Fatality fatality = WARNING;
const char * filename = "\0";
extern int line_number;
extern int yylex();
%}

%union {
    ast::ASTPtr *a;
    ast::ASTList *al;
    types::TypePtr *tp;
    int ival;
    char cval;
    const char *sval;
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
%token T_print "Print"

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
 


%type <tp> data_type
%type <tp> type
%type <tp> r_type
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
    : T_int     { $$ = &types::intType;  }
    | T_byte    { $$ = &types::byteType; }
    ;

type
    : data_type '[' ']' { $$ = new types::TypePtr(std::make_shared<types::ArrayType>(*$1)); }
    | data_type         { $$ = $1;                                               }
    ;

r_type
    : data_type         { $$ = $1;                                   }
    | "proc"            { $$ = new types::TypePtr(std::make_shared<types::VoidType>()); } 
    ;

cond
    : "true"            { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>("true"));       }
    | "false"           { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>("false"));      }
    | '(' cond ')'      { $$ = $2;                                              }
    | '!' cond          { $$ = $2;                                              }
    | expr '<' expr     { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>("<", *$1, *$3));  }
    | expr '>' expr     { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>(">", *$1, *$3));  }
    | expr "==" expr    { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>("==", *$1, *$3)); }
    | expr "!=" expr    { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>("!=", *$1, *$3)); }
    | expr "<=" expr    { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>("<=", *$1, *$3)); }
    | expr ">=" expr    { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>(">=", *$1, *$3)); }
    | cond '&' cond     { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>("&", *$1, *$3));  }
    | cond '|' cond     { $$ = new ast::ASTPtr(std::make_shared<ast::Cond>("|", *$1, *$3));  }
    ;

l_value
    : T_string          { $$ = new ast::ASTPtr(std::make_shared<ast::String>($1));       }
    | T_id '[' expr ']' { $$ = new ast::ASTPtr(std::make_shared<ast::LValue>($1, *$3));   }
    | T_id              { $$ = new ast::ASTPtr(std::make_shared<ast::LValue>($1));       }
    ;

expr
    : T_char            { $$ = new ast::ASTPtr(std::make_shared<ast::Char>($1));          }
    | T_const           { $$ = new ast::ASTPtr(std::make_shared<ast::Const>($1));          } 
    | l_value           { $$ = $1;                                               }
    | '(' expr ')'      { $$ = $2;                                               }
    | func_call         { $$ = $1;                                               }
    | '+' expr          { $$ = new ast::ASTPtr(std::make_shared<ast::BinOp>('+', *$2));     }
    | '-' expr          { $$ = new ast::ASTPtr(std::make_shared<ast::BinOp>('-', *$2));     }
    | expr '+' expr     { $$ = new ast::ASTPtr(std::make_shared<ast::BinOp>('+', *$1, *$3)); }
    | expr '-' expr     { $$ = new ast::ASTPtr(std::make_shared<ast::BinOp>('-', *$1, *$3)); }
    | expr '*' expr     { $$ = new ast::ASTPtr(std::make_shared<ast::BinOp>('*', *$1, *$3)); }
    | expr '/' expr     { $$ = new ast::ASTPtr(std::make_shared<ast::BinOp>('/', *$1, *$3)); }
    | expr '%' expr     { $$ = new ast::ASTPtr(std::make_shared<ast::BinOp>('%', *$1, *$3)); }
    ;


expr_list 
    :                      { $$ = new ast::ASTList();                     }
    | expr_list ',' expr   { $1->push_back(*$3); $$ = $1;                 }
    | expr                 { $$ = new ast::ASTList(); $$->push_back(*$1); }
    ;

func_call
    : T_id '(' expr_list ')' { $$ = new ast::ASTPtr(std::make_shared<ast::Call>($1, *$3)); }
    ;

stmt
    : ';'                                   { $$ = nullptr;            }
    | "Print" expr ';'                        { $$ = new ast::ASTPtr(std::make_shared<ast::Print>(*$2)); }
    | l_value '=' expr ';'                  { $$ = new ast::ASTPtr(std::make_shared<ast::Assign>(*$1, *$3)); }
    | compound_stmt                         { $$ = $1;                 }
    | func_call ';'                         { $$ = $1;                 }
    | "if" '(' cond ')' stmt                { $$ = new ast::ASTPtr(std::make_shared<ast::If>(*$3, *$5));     }
    | "if" '(' cond ')' stmt "else" stmt    { $$ = new ast::ASTPtr(std::make_shared<ast::If>(*$3, *$5, *$7)); }
    | "while" '(' cond ')' stmt             { $$ = new ast::ASTPtr(std::make_shared<ast::While>(*$3, *$5));  }
    | "return" expr ';'                     { $$ = new ast::ASTPtr(std::make_shared<ast::Return>(*$2));     }
    ;

stmt_list
    :                   { $$ = new ast::ASTList();      }
    | stmt_list stmt    { $1->push_back(*$2); $$ = $1; }
    ;

compound_stmt
    : '{' stmt_list '}' { $$ = new ast::ASTPtr(std::make_shared<ast::Block>(*$2)); }
    ;


var_def
    : T_id ':' data_type';'                  
    { $$ = new ast::ASTPtr(std::make_shared<ast::VarDef>($1, *$3));     }
    | T_id ':' data_type '[' T_const ']' ';' 
    { $$ = new ast::ASTPtr(std::make_shared<ast::VarDef>($1, *$3, $5)); }
    ;

local_def
    : func_def  { $$ = $1; }
    | var_def   { $$ = $1; }
    ;

local_def_list
    :                          { $$ = new ast::ASTList();     }
    | local_def_list local_def { $1->push_back(*$2); $$ = $1; }
    ;



fpar_def
    : T_id ':' "reference" type { $$ = new ast::ASTPtr(std::make_shared<ast::Param>($1, "reference", *$4)); }
    | T_id ':' type             { $$ = new ast::ASTPtr(std::make_shared<ast::Param>($1, "value" , *$3));    }
    ;

fpar_list
    :                        { $$ = new ast::ASTList();                     }
    | fpar_list ',' fpar_def { $1->push_back(*$3); $$ = $1;                 }
    | fpar_def               { $$ = new ast::ASTList(); $$->push_back(*$1); }
    ;

func_def
    : T_id '(' fpar_list ')' ':' r_type local_def_list compound_stmt 
    { $$ = new ast::ASTPtr(std::make_shared<ast::Func>($1, *$3, *$6, *$7, *$8)); }
    ;

program
    : func_def {sym::Table vars;
                std::static_pointer_cast<ast::Func>(*$1)->sem(vars);
                $$ = $1;}
    ;

%%

int main(int argc, char *argv[]) {
    

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-Wonce")
            fatality = FATAL;

        size_t pos = arg.find_last_of('.');
        if (pos != std::string::npos && arg.substr(pos + 1) == "alan") {
            filename = argv[i];
        }
    }

    // if filename is not provided
    if (filename == "\0") {
        RaiseFileError(nofileError_c);
    }


    FILE *inputFile = fopen(filename, "r");

    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return 1;
    }

    yyin = inputFile;  // Set yyin to read from the provided file

    int res = yyparse();  // Use the generated parser
    fclose(inputFile);   // Close the file when done

    return 0;
}

