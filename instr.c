
#include "instr.h"

unsigned char mask_bits(unsigned int val, int n)
{
    return (unsigned char)(val % (0b1 << n));
}

void write_binary_data(unsigned char *data, int to, int from, unsigned int val)
{
    int byteOffset = from / 8;
    while (byteOffset <= to / 8)
    {
        unsigned char byte;
        if (from / 8 == byteOffset && from % 8 > 0)
        {
            byte = (mask_bits(data[byteOffset], from % 8)) | (mask_bits(val, 8 - from % 8) << from % 8);
            val >>= 8 - from % 8;
        }
        else
        {
            byte = val;
            val >>= 8;
        }
        if ((to + 1) / 8 == byteOffset)
        {
            byte = (data[byteOffset] & (0xff << (to + 1) % 8)) | (mask_bits(byte, (to + 1) % 8));
        }
        data[byteOffset++] = byte;
    }
}

instr_t *instr_R_type(instr_codes_t instr_codes, int rd, int rs1, int rs2)
{
    instr_t *instr = malloc(sizeof(instr_t));
    instr->data = calloc(4, sizeof(unsigned char));
    write_binary_data(instr->data, 6, 0, instr_codes.opcode);
    write_binary_data(instr->data, 11, 7, rd);
    write_binary_data(instr->data, 14, 12, instr_codes.funct3);
    write_binary_data(instr->data, 19, 15, rs1);
    write_binary_data(instr->data, 24, 20, rs2);
    write_binary_data(instr->data, 31, 25, instr_codes.funct7);
    return instr;
}
