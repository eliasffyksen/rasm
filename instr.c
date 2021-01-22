
#include "bin/parser.h"
#include "instr.h"

unsigned char mask_bits(unsigned int val, int n) {
    return (unsigned char)(val % (0b1 << n));
}

void write_binary_data(unsigned char* data, int from, int to, unsigned int val) {
    int byteOffset = from / 8;
    while (byteOffset <= to / 8) {
        unsigned char byte;
        if (from / 8 == byteOffset && from % 8 > 0) {
            byte = (mask_bits(data[byteOffset], from % 8))
                 | (mask_bits(val, 8 - from % 8) << from % 8);
            val >>= 8 - from % 8;
        } else {
            byte = val;
            val >>= 8;
        }
        if ((to + 1) / 8 == byteOffset) {
            byte = (data[byteOffset] & (0xff << (to + 1) % 8))
                 | (mask_bits(byte, (to + 1) % 8));
        }
        data[byteOffset++] = byte;
    }
}

instr_t* instr_R_type(int opcode, int funct3, int funct7, int rd, int rs1, int rs2) {
    instr_t* instr = malloc(sizeof(instr_t));
    instr->data = calloc(4, sizeof(unsigned char));
    write_binary_data(instr->data, 0, 6, opcode);
    write_binary_data(instr->data, 7, 11, rd);
    write_binary_data(instr->data, 12, 14, funct3);
    write_binary_data(instr->data, 15, 19, rs1);
    write_binary_data(instr->data, 20, 24, rs2);
    write_binary_data(instr->data, 25, 31, funct7);
    return instr;
}

instr_t* instr_alu(yytoken_kind_t instr, int rd, int rs1, int rs2) {
    switch (instr) {
        case ADD: return instr_R_type(0b0110011, 0b000, 0b0000000, rd, rs1, rs2);
        default: printf("Unimplemented ALU instr %d!!!", instr); exit(1);
    }
    return (void*) 0;
}
