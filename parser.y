
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
    yytoken_kind_t token;
    instr_t* instr;
    char* str;
    int num;
}

%token NEW_LINE COLON COMMA
%token <token> ADD
%token <num> REG
%token <str> IDENTIFIER

%type <token> alu_instr
%type <instr> instr

%%

list: /* nothing */
    | list instr NEW_LINE { line_number++; add_instr($2); }
    | list NEW_LINE { line_number++; }
    ;

instr: alu_instr REG COMMA REG COMMA REG { $$ = instr_alu($1, $2, $4, $6); }
     ;

alu_instr: ADD
         ;

lable: IDENTIFIER COLON
     ;
