
#include "main.h"

int debug = 1;
int line_number = 0;

int main(int argc, char **argv)
{
    line_number = 1;
    yyparse();
}

void add_instr(instr_t *instr)
{
    if (debug)
        print_instr(instr);
    free(instr->data);
    free(instr);
}

void yyerror()
{
    printf("syntax error on line: %d\nI give up!\n", line_number);
    exit(1);
}
