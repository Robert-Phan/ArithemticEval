#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

int main(int argc, char const *argv[])
{
    TokenList *list = scan("1*2");
    Expr *tree = parse(list);
    
    return 0;
}
