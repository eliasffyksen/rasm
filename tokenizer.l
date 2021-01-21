
%option noyywrap

%{
    #include <string.h>
    #include "parser.h"
    #include "../main.h"
%}

%%

(?i:add)                { yylval.token = ADD; return ADD; }

(?i:x([0-9]|[1-2][0-9]|3[0-2])) { yylval.num = atoi(yytext + 1); return REG; }
(?i:S0)                         { yylval.num = 8; return REG; }
(?i:S1)                         { yylval.num = 9; return REG; }
(?i:S([2-9]|10|11))             { yylval.num = 16 + atoi(yytext + 1); return REG; }


:                       { return COLON; }
,                       { return COMMA; }
;.*                     {}
\n                      { return NEW_LINE; }

[a-zA-Z][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return IDENTIFIER; }

[ \n\t\r]+              {}
.                       { printf("Failed to parse char: '%c'\n", yytext[0]); }
