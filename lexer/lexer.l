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
%}

L [a-zA-Z]
D [0-9]
W [ \t\n\r]

%%

"byte" { return T_byte; }
"else" { return T_else; }
"false" { return T_false; }
"if" { return T_if; }
"int" { return T_int; }
"proc" { return T_proc; }
"reference" { return T_reference; }
"return" { return T_return; }
"while" { return T_while; }
"true" { return T_true; }

[=\+\-\*/%\(\)] { return yytext[0];}

{L} { return T_id; }
{D}+ { return T_const; }

{W}+ { /* nothing */ }
\'.*\n' { /* nothing */ }

. { fprintf(stderr, "illegal character\n"); exit(1); }
%%

int main() {
    int token;
    do {
        token = yylex();
        printf("token=%d, lexeme=\"%s\"\n", token, yytext);
    } while (token != T_eof);
}
