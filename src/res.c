#include "res.h"

void ResApply(int delay)
{
    BOOL apply = FALSE;
    struct WindowInfo wininfo;
    struct Profile prof;

    for (;;)
    {
        Sleep(delay);

        wininfo = GetForegroundWindowInfo();
        prof = ProfileLoad(wininfo.title, wininfo.exe);
        free(wininfo.title);

        if (strcmp(wininfo.exe, "ApplicationFrameHost.exe") == 0)
        {
            if (prof.title == TRUE)
            {
                apply = TRUE;
            }
        }
        else if ((prof.exe == TRUE) && (strcmp(wininfo.exe, ".") != 0))
        {
            apply = TRUE;
        }

        if (apply == TRUE)
        {
            DEVMODE devmode;
            devmode.dmPelsWidth = atoi(strtok(prof.res, "x"));
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
    struct WindowInfo wininfo;
    struct Profile prof;

    for (;;)
    {
        Sleep(delay);

        wininfo = GetForegroundWindowInfo();
        prof = ProfileLoad(wininfo.title, wininfo.exe);
        free(wininfo.title);

        if (strcmp(wininfo.exe, "ApplicationFrameHost.exe") == 0)
        {
            if (prof.title == FALSE)
            {
                reset = TRUE;
            }
        }
        else if ((prof.exe == FALSE) && (strcmp(wininfo.exe, ".") != 0))
        {
            reset = TRUE;
        };

        if (reset == TRUE)
        {
            ChangeDisplaySettings(NULL, 0);
            break;
        }
    }
    ResApply(delay);
}