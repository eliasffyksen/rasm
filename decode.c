
#include "decode.h"

instr_type_e get_instr_type(unsigned char* data) {
    unsigned int opcode = bin_to_int(data, 6, 0);
    switch (opcode) {
        case 0b0110011: return R_type;
        case 0b0010011: return I_type;
        default: 
            puts("Unknown instruction type in get_instr_type!!!");
            exit(1);
    }
    return 0;
}

unsigned int bin_to_int(unsigned char* data, int from, int to) {
    unsigned int res = 0;
    for (int i = from; i >= to; i--) {
        int byteOffset = i / 8;
        int bitOffset = i % 8;
        int bit = (data[byteOffset] >> bitOffset) & 1;
        res <<= 1;
        if (bit) res |= 1;
    }
    return res;
}

void print_bin(unsigned int val, int bits) {
    if (bits == 0)
        return;
    print_bin(val >> 1, bits - 1);
    printf(val & 1 ? "1" : "0");
}

void print_instr_R_type(unsigned char* data) {
    printf("+---------+-----+-----+--------+-----+---------+\n");
    printf("|  funct7 | rs2 | rs1 | funct3 |  rd |  opcode |\n");
    printf("+---------+-----+-----+--------+-----+---------+\n");
    printf("| "); print_bin(bin_to_int(data, 31, 25), 7); printf(" "); // funct7
    printf("| x%02d ", bin_to_int(data, 24, 20)); // rs2
    printf("| x%02d ", bin_to_int(data, 19, 15)); // rs1
    printf("|    "); print_bin(bin_to_int(data, 14, 12), 3); printf(" "); // funct3
    printf("| x%02d ", bin_to_int(data, 11, 7)); // rd
    printf("| "); print_bin(bin_to_int(data, 6, 0), 7); printf(" |\n"); // opcode
    printf("+---------+-----+-----+--------+-----+---------+\n");
}

void print_instr_I_type(unsigned char* data) {
    printf("+---------------+-----+--------+-----+---------+\n");
    printf("|    immi[11:0] | rs1 | funct3 |  rd |  opcode |\n");
    printf("+---------------+-----+--------+-----+---------+\n");
    printf("|         0x%03x ", bin_to_int(data, 31, 20)); // Immi[11:0]
    printf("| x%02d ", bin_to_int(data, 19, 15)); // rs1
    printf("|    "); print_bin(bin_to_int(data, 14, 12), 3); printf(" "); // funct3
    printf("| x%02d ", bin_to_int(data, 11, 7)); // rd
    printf("| "); print_bin(bin_to_int(data, 6, 0), 7); printf(" |\n"); // opcode
    printf("+---------------+-----+--------+-----+---------+\n");
}

void print_instr(instr_t* instr) {
    switch (get_instr_type(instr->data)) {
        case R_type: print_instr_R_type(instr->data); break;
        case I_type: print_instr_I_type(instr->data); break;
        default:
            puts("Unknown instruction type in print_instr!!!");
            exit(1);
    }
}
