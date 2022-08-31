#include "funcs.h"
#include "helpers.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    chdir(dirname(argv[0]));
    OptsExist();
    ResApply();
    return 0;
}