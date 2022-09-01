#include "res.h"

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

void ResApply()
{
    BOOL apply = FALSE;
    char *res;
    for (;;)
    {
        Sleep(AutoDelay());
        struct WindowInfo wi = GetForegroundWindowInfo();
        printf("%s | %s \n", wi.title, wi.exe);
        if (strcmp(wi.exe, "ApplicationFrameHost.exe") == 0)
        {
            if (ProfCheck(wi.title) == TRUE)
            {
                res = ProfLoad(wi.title);
                apply = TRUE;
            }
        }
        else if ((ProfCheck(wi.exe) == TRUE) && (strcmp(wi.exe, ".") != 0))
        {
            res = ProfLoad(wi.exe);
            apply = TRUE;
        }

        free(wi.title);
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
    for (;;)
    {
        Sleep(AutoDelay());
        struct WindowInfo wi = GetForegroundWindowInfo();
        printf("%s | %s \n", wi.title, wi.exe);
        if (strcmp(wi.exe, "ApplicationFrameHost.exe") == 0)
        {
            if (ProfCheck(wi.title) == FALSE)
            {
                reset = TRUE;
            }
        }
        else if ((ProfCheck(wi.exe) == FALSE) && (strcmp(wi.exe, ".") != 0))
        {
            reset = TRUE;
        };

        free(wi.title);
        if (reset == TRUE)
        {
            ChangeDisplaySettings(NULL, 0);
            break;
        }
    }
    ResApply();
}