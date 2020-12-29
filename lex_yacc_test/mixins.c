#include <stdio.h>

int yyerror(char *s) {
    printf("%s\n", s);
}

int yywrap() {
}
