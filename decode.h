
#ifndef _DECODE_H
#define _DECODE_H

#include <stdlib.h>
#include <stdio.h>

#include "AST.h"

enum instr_type {
    R_type
};
typedef enum instr_type instr_type_e;

instr_type_e get_instr_type(unsigned char* data);
void print_instr(instr_t* instr);
void print_bin(unsigned int val, int bits);
unsigned int bin_to_int(unsigned char* data, int from, int to);

#endif /* _INSTR_H */