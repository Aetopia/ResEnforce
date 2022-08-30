#include "funcs.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{  
    chdir(GetFileDir(argv[0]));
    ResEnforce();
}