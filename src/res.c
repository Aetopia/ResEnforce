#include "res.h"

void ResApply(int delay)
{
    BOOL apply = FALSE;
    struct Window win;
    struct Profile prof;

    for (;;)
    {
        win = GetForegroundWindowInfo();
        prof = ProfileLoad(win.title, win.exe);
        free(win.title);

        if (strcmp(win.exe, "ApplicationFrameHost.exe") == 0)
        {
            if (prof.title == TRUE)
            {
                apply = TRUE;
            }
        }
        else if (prof.exe == TRUE)
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
        Sleep(delay);
    }
    ResReset(delay);
}

void ResReset(int delay)
{
    BOOL reset = FALSE;
    struct Window win;
    struct Profile prof;

    for (;;)
    {

        win = GetForegroundWindowInfo();
        prof = ProfileLoad(win.title, win.exe);
        free(win.title);

        if (strcmp(win.exe, "ApplicationFrameHost.exe") == 0)
        {
            if (prof.title == FALSE)
            {
                reset = TRUE;
            }
        }
        else if (prof.exe == FALSE)
        {
            reset = TRUE;
        };

        if (reset == TRUE)
        {
            ChangeDisplaySettings(NULL, 0);
            break;
        }
        Sleep(delay);
    }
    ResApply(delay);
}