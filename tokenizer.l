
%option noyywrap

%{
    #include <string.h>
    #include "parser.tab.h"
    #include "../main.h"
%}

%%

(?i:ADD)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b000, .funct7 = 0b0000000}; return R_TYPE; }
(?i:SUB)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b000, .funct7 = 0b0100000}; return R_TYPE; }
(?i:SLL)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b001, .funct7 = 0b0000000}; return R_TYPE; }
(?i:SLT)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b010, .funct7 = 0b0000000}; return R_TYPE; }
(?i:SLTU)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b011, .funct7 = 0b0000000}; return R_TYPE; }
(?i:XOR)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b100, .funct7 = 0b0000000}; return R_TYPE; }
(?i:SRL)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b101, .funct7 = 0b0000000}; return R_TYPE; }
(?i:SRA)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b101, .funct7 = 0b0100000}; return R_TYPE; }
(?i:OR)     { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b110, .funct7 = 0b0000000}; return R_TYPE; }
(?i:AND)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b111, .funct7 = 0b0000000}; return R_TYPE; }

(?i:x([0-9]|[1-2][0-9]|3[0-1])) { yylval.num = atoi(yytext + 1); return REG; }
(?i:S0)                         { yylval.num = 8; return REG; }
(?i:S1)                         { yylval.num = 9; return REG; }
(?i:S([2-9]|10|11))             { yylval.num = 16 + atoi(yytext + 1); return REG; }

:                       { return COLON; }
,                       { return COMMA; }
;.*                     {}
\n                      { return NEW_LINE; }

[a-zA-Z][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return IDENTIFIER; }

[ \t\r]+                {}
.                       { printf("Failed to parse char: '%c'\n", yytext[0]); }
