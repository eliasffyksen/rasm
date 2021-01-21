
#include "bin/parser.h"

void alu_instr(yytoken_kind_t instr, int xD, int xL, int xR) {
    switch (instr) {
        case ADD: printf("Add instruction %d %d %d\n", xD, xL, xR); break;
        default: printf("Unimplemented ALU instr %d!!!", instr); break;
    }
}