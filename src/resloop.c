#include "resloop.h"

int AutoDelay()
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int cpu_count = sysinfo.dwNumberOfProcessors;
    if (cpu_count <= 4)
    {
        return 1000;
    }
    else
    {
        return 100;
    }
}

void ResEnforce()
{
    BOOL apply = FALSE;
    int delay = AutoDelay();
    char *res;
    for (;;)
    {
        Sleep(delay);
        struct WindowInfo wi = GetForegroundWindowInfo();
        char *title = wi.title;
        char *exe = basename(wi.exe);

        if (strcmp(exe, "ApplicationFrameHost.exe") == 0)
        {
            if (ProfCheck(title) == TRUE)
            {
                res = ProfLoad(title);
                apply = TRUE;
            }
        }
        else if (ProfCheck(exe) == TRUE)
        {
            res = ProfLoad(exe);
            apply = TRUE;
        }

        free(wi.title);
        free(wi.exe);
        if (apply == TRUE)
        {
            DEVMODE devmode;
            devmode.dmPelsWidth = atoi(strtok(res, "x"));
            devmode.dmPelsHeight = atoi(strtok(NULL, "x"));
            devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
            devmode.dmSize = sizeof(DEVMODE);
            ChangeDisplaySettings(&devmode, 0);
            break;
        }
    }
    ResReset();
}

void ResReset()
{
    BOOL reset = FALSE;
    int delay = AutoDelay();
    for (;;)
    {
        Sleep(delay);
        struct WindowInfo wi = GetForegroundWindowInfo();
        char *title = wi.title;
        char *exe = basename(wi.exe);

        if (strcmp(exe, "ApplicationFrameHost.exe") == 0)
        {
            if (ProfCheck(title) == FALSE)
            {
                reset = TRUE;
            }
        }
        else if (ProfCheck(exe) == FALSE)
        {
            reset = TRUE;
        };

        free(wi.title);
        free(wi.exe);
        if (reset == TRUE)
        {
            ChangeDisplaySettings(NULL, 0);
            break;
        }
    }
    ResEnforce();
}