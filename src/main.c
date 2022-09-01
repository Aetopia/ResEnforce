#include "winhook.h"
#include "opts.h"
#include "resloop.h"

int main(int argc, char *argv[])
{
    chdir(dirname(argv[0]));
    OptsExist();
    ResEnforce();
    return 0;
}