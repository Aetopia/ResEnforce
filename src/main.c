#include "funcs.h"
#include <stdio.h>

int main(int argc, char *argv[])
{  
    chdir(dirname(argv[0]));
    OptsExist();
    ResApply();
}