#include "res.h"

void ResApply(int delay)
{
    BOOL apply = FALSE;
    char *res;
    for (;;)
    {
        Sleep(delay);
        struct WindowInfo wi = GetForegroundWindowInfo();

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
    ResReset(delay);
}

void ResReset(int delay)
{
    BOOL reset = FALSE;
    for (;;)
    {
        Sleep(delay);
        struct WindowInfo wi = GetForegroundWindowInfo();

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
    ResApply(delay);
}