
#ifndef _INSTR_H
#define _INSTR_H

#include <stdlib.h>
#include <stdio.h>

#include "bin/parser.h"

void alu_instr(yytoken_kind_t instr, int xD, int xL, int xR);

struct instr {
    unsigned char* data;
};
typedef struct instr instr_t;

#endif /* _INSTR_H */