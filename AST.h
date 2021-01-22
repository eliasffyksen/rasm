
#ifndef _AST_H
#define _AST_H

struct instr {
    unsigned char* data;
};
typedef struct instr instr_t;

struct instr_codes {
    int opcode, funct3, funct7;
};
typedef struct instr_codes instr_codes_t;

#endif
