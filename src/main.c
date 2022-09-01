#include "winhook.h"
#include "opts.h"
#include "res.h"

int main(int argc, char *argv[])
{
    (void)argc;
    chdir(dirname(argv[0]));
    OptsExist();
    ResApply();
    return 0;
}