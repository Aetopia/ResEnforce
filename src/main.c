#include "winhook.h"
#include "opts.h"
#include "res.h"

int main(int, char *argv[])
{
    int delay;
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int cpu_count = sysinfo.dwNumberOfProcessors;
    if (cpu_count <= 4)
    {
        delay = 1000;
    }
    else
    {
        delay = 100;
    }
    chdir(dirname(argv[0]));
    OptsExist();
    ResApply(delay);
    return 0;
}