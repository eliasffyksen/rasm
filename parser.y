%{
    // Bison does not decleare this function properly
    int yylex();

    #include "../main.h"
    #include "../instr.h"
    #include "parser.h"
%}

%union {
    yytoken_kind_t token;
    char* str;
    int num;
}

%token NEW_LINE COLON COMMA
%token <token> ADD
%token <num> REG
%token <str> IDENTIFIER

%type <token> alu_instr

%%

list: /* nothing */
    | list instr NEW_LINE { line_number++; }
    | list NEW_LINE { line_number++; }
    ;

instr: alu_instr REG COMMA REG COMMA REG { alu_instr($1, $2, $4, $6); }
     ;

alu_instr: ADD { $$ = $1; }
         ;

lable: IDENTIFIER COLON
     ;
