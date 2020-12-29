#include <stdio.h>
#include "grammar.tab.h"

int main() {
    int result = 0;
    int count = 0;
    return yyparse();
}
