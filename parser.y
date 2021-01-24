
%code requires {
    #include "../AST.h"
}

%{
    // Bison does not decleare this function properly
    int yylex();

    #include "../main.h"
    #include "parser.tab.h"
%}

%union {
    instr_codes_t instr_codes;
    instr_t* instr;
    char* str;
    int num;
}

%token NEW_LINE COLON COMMA NEG
%token <instr_codes> R_TYPE I_TYPE I_SHAMT_TYPE B_TYPE U_TYPE J_TYPE S_TYPE
%token <num> REG NUM
%token <str> IDENTIFIER

%type <instr> instr
%type <num> num

%%

list: /* nothing */
    | list instr NEW_LINE { line_number++; add_instr($2); }
    | list NEW_LINE { line_number++; }
    ;

instr: R_TYPE REG COMMA REG COMMA REG       { $$ = instr_R_type($1, $2, $4, $6); }
     | I_TYPE REG COMMA REG COMMA num       { $$ = instr_I_type($1, $2, $4, $6); }
     | I_SHAMT_TYPE REG COMMA REG COMMA num { $$ = instr_I_SHAMT_type($1, $2, $4, $6); }
     | B_TYPE REG COMMA REG COMMA num       { $$ = instr_B_type($1, $2, $4, $6); }
     | U_TYPE REG COMMA num                 { $$ = instr_U_type($1, $2, $4); }
     | J_TYPE REG COMMA num                 { $$ = instr_J_type($1, $2, $4); }
     | S_TYPE REG COMMA num COMMA REG       { $$ = instr_S_type($1, $2, $4, $6); }
     ;

num: NUM
   | NEG NUM { $$ = -$2; };
   ;
