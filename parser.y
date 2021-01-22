
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

%token NEW_LINE COLON COMMA
%token <instr_codes> R_TYPE
%token <num> REG
%token <str> IDENTIFIER

%type <instr_codes> alu_instr
%type <instr> instr

%%

list: /* nothing */
    | list instr NEW_LINE { line_number++; add_instr($2); }
    | list NEW_LINE { line_number++; }
    ;

instr: R_TYPE REG COMMA REG COMMA REG { $$ = instr_R_type($1, $2, $4, $6); }
     ;

lable: IDENTIFIER COLON
     ;
