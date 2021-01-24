
#include "decode.h"

instr_type_e get_instr_type(unsigned char *data)
{
    unsigned int opcode = bin_to_int(data, 6, 0);
    unsigned int funct3 = bin_to_int(data, 14, 12);
    switch (opcode)
    {
    case 0b0110011:
        return R_type;
    case 0b0010011:
        switch (funct3)
        {
        case 0b001:
        case 0b101:
            return I_SHAMT_type;
        default:
            return I_type;
        }
    case 0b1100111:
        return I_type;
    case 0b1100011:
        return B_type;
    case 0b0110111:
    case 0b0010111:
        return U_type;
    case 0b1101111:
        return J_type;
    default:
        puts("Unknown instruction type in get_instr_type!!!");
        exit(1);
    }
    return 0;
}

unsigned int bin_to_int(unsigned char *data, int from, int to)
{
    unsigned int res = 0;
    for (int i = from; i >= to; i--)
    {
        int byteOffset = i / 8;
        int bitOffset = i % 8;
        int bit = (data[byteOffset] >> bitOffset) & 1;
        res <<= 1;
        if (bit)
            res |= 1;
    }
    return res;
}

void print_bin(unsigned int val, int bits)
{
    if (bits == 0)
        return;
    print_bin(val >> 1, bits - 1);
    printf(val & 1 ? "1" : "0");
}

void print_instr_R_type(unsigned char *data)
{
    printf("+---------+-----+-----+--------+-----+---------+\n");
    printf("|  funct7 | rs2 | rs1 | funct3 |  rd |  opcode |\n");
    printf("+---------+-----+-----+--------+-----+---------+\n");
    printf("| ");
    print_bin(bin_to_int(data, 31, 25), 7);
    printf(" ");                                  // funct7
    printf("| x%02d ", bin_to_int(data, 24, 20)); // rs2
    printf("| x%02d ", bin_to_int(data, 19, 15)); // rs1
    printf("|    ");
    print_bin(bin_to_int(data, 14, 12), 3);
    printf(" ");                                 // funct3
    printf("| x%02d ", bin_to_int(data, 11, 7)); // rd
    printf("| ");
    print_bin(bin_to_int(data, 6, 0), 7);
    printf(" |\n"); // opcode
    printf("+---------+-----+-----+--------+-----+---------+\n");
}

void print_instr_I_type(unsigned char *data)
{
    printf("+---------------+-----+--------+-----+---------+\n");
    printf("|    immi[11:0] | rs1 | funct3 |  rd |  opcode |\n");
    printf("+---------------+-----+--------+-----+---------+\n");
    printf("|         0x%03x ", bin_to_int(data, 31, 20)); // Immi[11:0]
    printf("| x%02d ", bin_to_int(data, 19, 15));          // rs1
    printf("|    ");
    print_bin(bin_to_int(data, 14, 12), 3);
    printf(" ");                                 // funct3
    printf("| x%02d ", bin_to_int(data, 11, 7)); // rd
    printf("| ");
    print_bin(bin_to_int(data, 6, 0), 7);
    printf(" |\n"); // opcode
    printf("+---------------+-----+--------+-----+---------+\n");
}

void print_instr_I_SHAMT_type(unsigned char *data)
{
    printf("+---------+-----+-----+--------+-----+---------+\n");
    printf("|  funct7 |shamt| rs1 | funct3 |  rd |  opcode |\n");
    printf("+---------+-----+-----+--------+-----+---------+\n");
    printf("| ");
    print_bin(bin_to_int(data, 31, 25), 7);
    printf(" ");                                  // funct7
    printf("| 0x%02x", bin_to_int(data, 19, 15)); // shamt
    printf("| x%02d ", bin_to_int(data, 19, 15)); // rs1
    printf("|    ");
    print_bin(bin_to_int(data, 14, 12), 3);
    printf(" ");                                 // funct3
    printf("| x%02d ", bin_to_int(data, 11, 7)); // rd
    printf("| ");
    print_bin(bin_to_int(data, 6, 0), 7);
    printf(" |\n"); // opcode
    printf("+---------------+-----+--------+-----+---------+\n");
}

void print_instr_B_type(unsigned char *data)
{
    printf("+----------+----+----+------+----------+-------+\n");
    printf("|O[12|10:5]| rs2| rs1|funct3| O[4:1|11]| opcode|\n");
    printf("+----------+----+----+------+----------+-------+\n");
    printf("| ");
    print_bin(bin_to_int(data, 31, 31), 1); // offset[12]
    printf(" ");
    print_bin(bin_to_int(data, 30, 25), 6); // offset[10:5]
    printf(" | x%02d", bin_to_int(data, 24, 20)); // rs1
    printf("| x%02d|  ", bin_to_int(data, 19, 15)); // rs2
    print_bin(bin_to_int(data, 14, 12), 3); // funct3
    printf(" |   ");
    print_bin(bin_to_int(data, 11, 8), 4); // offset[4:1]
    printf(" ");
    print_bin(bin_to_int(data, 7, 7), 1); // offset[11]
    printf(" |");
    print_bin(bin_to_int(data, 6, 0), 7);
    printf("|\n"); // opcode
    printf("+----------+----+----+------+----------+-------+\n");
}

void print_instr_U_type(unsigned char *data) {
    printf("+------------------------------+-----+---------+\n");
    printf("|                  immi[31:12] |  rd |  opcode |\n");
    printf("+------------------------------+-----+---------+\n");
    printf("|         ");
    print_bin(bin_to_int(data, 31, 12), 20); // immi[31:12]
    printf(" | x%02d | ", bin_to_int(data, 11, 7)); // rd
    print_bin(bin_to_int(data, 6, 0), 7); // opcode
    printf(" |\n");
    printf("+------------------------------+-----+---------+\n");
}

void print_instr_J_type(unsigned char *data) {
    printf("+------------------------------+-----+---------+\n");
    printf("|       immi[20|10:1|11|19:12] |  rd |  opcode |\n");
    printf("+------------------------------+-----+---------+\n");
    printf("|      ");
    print_bin(bin_to_int(data, 31, 31), 1); // immi[20]
    printf(" ");
    print_bin(bin_to_int(data, 30, 21), 10); // immi[10:1]
    printf(" ");
    print_bin(bin_to_int(data, 20, 20), 1); // immi[11]
    printf(" ");
    print_bin(bin_to_int(data, 19, 12), 8); // immi[19:12]
    printf(" | x%02d | ", bin_to_int(data, 11, 7));
    print_bin(bin_to_int(data, 6, 0), 7); // opcode
    printf(" |\n");
    printf("+------------------------------+-----+---------+\n");
}

void print_instr(instr_t *instr)
{
    switch (get_instr_type(instr->data))
    {
    case R_type:
        print_instr_R_type(instr->data);
        break;
    case I_type:
        print_instr_I_type(instr->data);
        break;
    case I_SHAMT_type:
        print_instr_I_SHAMT_type(instr->data);
        break;
    case B_type:
        print_instr_B_type(instr->data);
        break;
    case U_type:
        print_instr_U_type(instr->data);
        break;
    case J_type:
        print_instr_J_type(instr->data);
        break;
    default:
        puts("Unknown instruction type in print_instr!!!");
        exit(1);
    }
}
