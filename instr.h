
#ifndef _INSTR_H
#define _INSTR_H

#include "bin/parser.h"

void alu_instr(yytoken_kind_t instr, int xD, int xL, int xR);

#endif /* _INSTR_H */