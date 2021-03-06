
#ifndef _INSTR_H
#define _INSTR_H

#include <stdlib.h>
#include <stdio.h>

#include "AST.h"
#include "bin/parser.tab.h"
#include "main.h"

instr_t *instr_R_type(instr_codes_t instr_codes, int rd, int rs1, int rs2);
instr_t *instr_I_type(instr_codes_t instr_codes, int rd, int rs1, int immi);
instr_t *instr_I_SHAMT_type(instr_codes_t instr_codes, int rd, int rs1, int immi);
instr_t *instr_B_type(instr_codes_t instr_codes, int rs1, int rs2, int immi);
instr_t *instr_U_type(instr_codes_t instr_codes, int rd, int immi);
instr_t *instr_J_type(instr_codes_t instr_codes, int rd, int immi);
instr_t *instr_S_type(instr_codes_t instr_codes, int rs1, int immi, int rs2);

#endif /* _INSTR_H */
