
#ifndef _MAIN_H
#define _MAIN_H

#include "instr.h"
#include "decode.h"
#include "bin/parser.tab.h"

extern int line_number;
extern int debug;
void yyerror();
void add_instr(instr_t* instr);

#endif