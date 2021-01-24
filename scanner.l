
%option noyywrap

%{
    #include <string.h>
    #include "parser.tab.h"
    #include "../main.h"
%}

%%

    /* --------------- ALU R_TYPE INSTRUCTIONS ----------------- */

(?i:ADD)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b000, .funct7 = 0b0000000 }; return R_TYPE; }
(?i:SUB)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b000, .funct7 = 0b0100000 }; return R_TYPE; }
(?i:SLL)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b001, .funct7 = 0b0000000 }; return R_TYPE; }
(?i:SLT)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b010, .funct7 = 0b0000000 }; return R_TYPE; }
(?i:SLTU)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b011, .funct7 = 0b0000000 }; return R_TYPE; }
(?i:XOR)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b100, .funct7 = 0b0000000 }; return R_TYPE; }
(?i:SRL)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b101, .funct7 = 0b0000000 }; return R_TYPE; }
(?i:SRA)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b101, .funct7 = 0b0100000 }; return R_TYPE; }
(?i:OR)     { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b110, .funct7 = 0b0000000 }; return R_TYPE; }
(?i:AND)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110011, .funct3 = 0b111, .funct7 = 0b0000000 }; return R_TYPE; }

    /* --------------- ALU IMMI I_TYPE INSTRUCTIONS ----------------- */

(?i:ADDI)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b000 }; return I_TYPE; }
(?i:SLTI)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b010 }; return I_TYPE; }
(?i:SLTIU)  { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b011 }; return I_TYPE; }
(?i:XORI)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b100 }; return I_TYPE; }
(?i:ORI)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b110 }; return I_TYPE; }
(?i:ANDI)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b111 }; return I_TYPE; }

    /* --------------- ALU IMMI SHAMT I_TYPE INSTRUCTIONS ----------------- */

(?i:SLLI)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b001, .funct7 = 0b0000000 }; return I_SHAMT_TYPE; }
(?i:SRLI)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b101, .funct7 = 0b0000000 }; return I_SHAMT_TYPE; }
(?i:SRAI)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010011, .funct3 = 0b101, .funct7 = 0b0100000 }; return I_SHAMT_TYPE; }

    /* --------------- CONDITIONAL BRANCH INSTRUCTIONS ----------------- */

(?i:BEQ)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b1100011, .funct3 = 0b000 }; return B_TYPE; }
(?i:BNE)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b1100011, .funct3 = 0b001 }; return B_TYPE; }
(?i:BLT)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b1100011, .funct3 = 0b100 }; return B_TYPE; }
(?i:BGE)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b1100011, .funct3 = 0b101 }; return B_TYPE; }
(?i:BLTU)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b1100011, .funct3 = 0b110 }; return B_TYPE; }
(?i:BGEU)   { yylval.instr_codes = (instr_codes_t){ .opcode = 0b1100011, .funct3 = 0b111 }; return B_TYPE; }

    /* --------------- UPPER IMMIDIATE INSTRUCTIONS --------------- */

(?i:LUI)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0110111 }; return U_TYPE; }
(?i:AUIPC)  { yylval.instr_codes = (instr_codes_t){ .opcode = 0b0010111 }; return U_TYPE; }

    /* --------------- UNCONDITIONAL JUMP INSTRUCTIONS --------------- */

(?i:JAL)    { yylval.instr_codes = (instr_codes_t){ .opcode = 0b1101111 }; return J_TYPE; }

    /* --------------- REGISTERS ----------------- */

zero    { yylval.num = 0; return REG; } // Always zero
ra      { yylval.num = 1; return REG; } // Call return address
sp      { yylval.num = 2; return REG; } // Stack pointer
gp      { yylval.num = 3; return REG; } // Global pointer
tp      { yylval.num = 4; return REG; } // Thread pointer
(?i:x([0-9]|[1-2][0-9]|3[0-1])) { yylval.num = atoi(yytext + 1);        return REG; } // X-prefix
(?i:t[0-2])                     { yylval.num = 5 + atoi(yytext + 1);    return REG; } // Temporary register 0-2
(?i:t[3-6])                     { yylval.num = 25 + atoi(yytext + 1);   return REG; } // Temporary register 3-6
(?i:S[0-1])                     { yylval.num = 8 + atoi(yytext + 1);    return REG; } // Saved register 0-1
(?i:S([2-9]|1[0-1]))            { yylval.num = 16 + atoi(yytext + 1);   return REG; } // Saved register 2-11
(?i:A[0-7])                     { yylval.num = 10 + atoi(yytext + 1);   return REG; } // Function argument 0-7

;.*                     {} // Comments
:                       { return COLON; }
,                       { return COMMA; }
\n                      { return NEW_LINE; }

[a-zA-Z][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return IDENTIFIER; } // Accept identifiers and lables

-               { return NEG; } // Negate number
[0-9]+          { yylval.num = atoi(yytext);                return NUM; } // Accept hex numbers
0x[0-9a-fA-F]+  { yylval.num = strtol(yytext, NULL, 16);    return NUM; } // Accept decimal numbers

[ \t\r]+                {}
.                       { printf("Failed to parse char: '%c'\n", yytext[0]); }
