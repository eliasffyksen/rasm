
#include "main.h"

int main(int argc, char **argv) {
    line_number = 1;
    yyparse();
}

void yyerror(){
	printf("syntax error on line: %d\nI give up!\n", line_number);
	exit(1);
}
