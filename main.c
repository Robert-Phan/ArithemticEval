#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "eval.h"

int main(int argc, char const *argv[])
{
    char buffer[256];

    fgets(buffer, sizeof(buffer), stdin);

    printf("%f\n", eval(buffer));

    return 0;
}
