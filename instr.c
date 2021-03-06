
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
    write_binary_data(instr->data, 31, 25, instr_codes.funct7);
    write_binary_data(instr->data, 24, 20, rs2);
    write_binary_data(instr->data, 19, 15, rs1);
    write_binary_data(instr->data, 14, 12, instr_codes.funct3);
    write_binary_data(instr->data, 11, 7, rd);
    write_binary_data(instr->data, 6, 0, instr_codes.opcode);
    return instr;
}

instr_t *instr_I_type(instr_codes_t instr_codes, int rd, int rs1, int immi)
{
    if (immi > 2047)
    {
        printf("ERROR ON LINE %d: immidiate value can not be more then 2047\n", line_number);
        exit(1);
    }
    else if (immi < -2048)
    {
        printf("ERROR ON LINE %d: immidiate value can not be less then -2048\n", line_number);
        exit(1);
    }

    instr_t *instr = malloc(sizeof(instr_t));
    instr->data = calloc(4, sizeof(unsigned char));
    write_binary_data(instr->data, 31, 20, immi);
    write_binary_data(instr->data, 19, 15, rs1);
    write_binary_data(instr->data, 14, 12, instr_codes.funct3);
    write_binary_data(instr->data, 11, 7, rd);
    write_binary_data(instr->data, 6, 0, instr_codes.opcode);
    return instr;
}

instr_t *instr_I_SHAMT_type(instr_codes_t instr_codes, int rd, int rs1, int immi)
{
    if (immi > 31)
    {
        printf("ERROR ON LINE %d: immidiate shamt for shifts can not be more then 31", line_number);
        exit(1);
    }
    else if (immi < 0)
    {
        printf("ERROR ON LINE %d: immidiate shamt for shifts can not be less then 0", line_number);
        exit(1);
    }
    instr_t *instr = malloc(sizeof(instr_t));
    instr->data = calloc(4, sizeof(unsigned char));
    write_binary_data(instr->data, 31, 25, instr_codes.funct7);
    write_binary_data(instr->data, 24, 20, immi);
    write_binary_data(instr->data, 19, 15, rs1);
    write_binary_data(instr->data, 14, 12, instr_codes.funct3);
    write_binary_data(instr->data, 11, 7, rd);
    write_binary_data(instr->data, 6, 0, instr_codes.opcode);
    return instr;
}

instr_t *instr_B_type(instr_codes_t instr_codes, int rs1, int rs2, int immi)
{
    if (immi > 4095)
    {
        printf("ERROR ON LINE %d: immidiate value can not be more then 4095\n", line_number);
        exit(1);
    }
    else if (immi < -4096)
    {
        printf("ERROR ON LINE %d: immidiate value can not be less then -4096\n", line_number);
        exit(1);
    }
    else if (immi % 2 != 0)
    {
        printf("ERROR ON LINE %d: immidiate branch value must be 16bit align (i.e. devisible by 2)\n", line_number);
        exit(1);
    }

    instr_t *instr = malloc(sizeof(instr_t));
    instr->data = calloc(4, sizeof(unsigned char));
    write_binary_data(instr->data, 31, 31, immi >> 12);
    write_binary_data(instr->data, 30, 25, immi >> 5);
    write_binary_data(instr->data, 24, 20, rs2);
    write_binary_data(instr->data, 19, 15, rs1);
    write_binary_data(instr->data, 14, 12, instr_codes.funct3);
    write_binary_data(instr->data, 11, 8, immi >> 1);
    write_binary_data(instr->data, 7, 7, immi >> 11);
    write_binary_data(instr->data, 6, 0, instr_codes.opcode);
    return instr;
}

instr_t *instr_U_type(instr_codes_t instr_codes, int rd, int immi)
{
    if (immi > 1048575)
    {
        printf("ERROR ON LINE %d: upper immidiate value can not be more then 1048575\n", line_number);
        exit(1);
    }
    else if (immi < -524288)
    {
        printf("ERROR ON LINE %d: upper immidiate value can not be less then -524288\n", line_number);
        exit(1);
    }

    instr_t *instr = malloc(sizeof(instr_t));
    instr->data = calloc(4, sizeof(unsigned char));
    write_binary_data(instr->data, 31, 12, immi); // immidiate[31:12]
    write_binary_data(instr->data, 11, 7, rd); // rd
    write_binary_data(instr->data, 6, 0, instr_codes.opcode);
    return instr;
}

instr_t *instr_J_type(instr_codes_t instr_codes, int rd, int immi)
{
    if (immi > 1048574)
    {
        printf("ERROR ON LINE %d: upper immidiate value can not be more then 1048575\n", line_number);
        exit(1);
    }
    else if (immi < -1048576)
    {
        printf("ERROR ON LINE %d: upper immidiate value can not be less then -1048576\n", line_number);
        exit(1);
    }
    else if (immi % 2 != 0)
    {
        printf("ERROR ON LINE %d: immidiate jump value must be 16bit align (i.e. devisible by 2)\n", line_number);
        exit(1);
    }

    instr_t *instr = malloc(sizeof(instr_t));
    instr->data = calloc(4, sizeof(unsigned char));
    write_binary_data(instr->data, 31, 31, immi >> 20); // immidiate[20]
    write_binary_data(instr->data, 30, 21, immi >> 1); // immidiate[10:1]
    write_binary_data(instr->data, 20, 20, immi >> 11); // immidiate[11]
    write_binary_data(instr->data, 19, 12, immi >> 12); // immidiate[19:12]
    write_binary_data(instr->data, 11, 7, rd); // rd
    write_binary_data(instr->data, 6, 0, instr_codes.opcode); // opcode
    return instr;
}

instr_t *instr_S_type(instr_codes_t instr_codes, int rs1, int immi, int rs2)
{
    if (immi > 2047)
    {
        printf("ERROR ON LINE %d: immidiate value can not be more then 2047\n", line_number);
        exit(1);
    }
    else if (immi < -2048)
    {
        printf("ERROR ON LINE %d: immidiate value can not be less then -2048\n", line_number);
        exit(1);
    }

    instr_t *instr = malloc(sizeof(instr_t));
    instr->data = calloc(4, sizeof(unsigned char));
    write_binary_data(instr->data, 31, 25, immi >> 5);
    write_binary_data(instr->data, 24, 20, rs1);
    write_binary_data(instr->data, 19, 15, rs2);
    write_binary_data(instr->data, 14, 12, instr_codes.funct3);
    write_binary_data(instr->data, 11, 7, immi);
    write_binary_data(instr->data, 6, 0, instr_codes.opcode);
    return instr;
}
