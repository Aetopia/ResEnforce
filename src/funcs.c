#include "funcs.h"

struct WindowInfo GetForegroundWindowInfo()
{
    HWND hwnd = GetForegroundWindow();
    char *filepath = GetExe(GetPID(hwnd));
    char *exe = basename(filepath);
    free(filepath);
    struct WindowInfo wininfo;
    wininfo.title = GetTitle(hwnd);
    wininfo.exe = exe;
    wininfo.pid = GetPID(hwnd);
    return wininfo;
}

void OptsExist()
{
    if (access("Options.ini", F_OK) == -1)
    {
        FILE *fptr;
        fptr = fopen("Options.ini", "w");
        fprintf(fptr, "[Profiles]\n"
                      "; Title or Executable Name = Resolution\n"
                      "; Example.exe = 1600x900\n"
                      "; Example = 1280x720 \n");
        fclose(fptr);
    }
}

BOOL ProfCheck(char *app)
{
    ini_t *ini = ini_load("Options.ini");
    const char *name = ini_get(ini, "Profiles", app);
    ini_free(ini);
    if (name == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

char *ProfLoad(char *app)
{
    ini_t *ini = ini_load("Options.ini");
    const char *name = ini_get(ini, "Profiles", app);
    ini_free(ini);
    return (char *)name;
}

void ResReset()
{
    BOOL reset = FALSE;
    int delay = AutoDelay();
    for (;;)
    {
        Sleep(delay);
        struct WindowInfo wi = GetForegroundWindowInfo();
        if (strcmp(wi.exe, "ApplicationFrameHost.exe") != 0)
        {
            if (ProfCheck(wi.exe) == FALSE)
            {
                reset = TRUE;
            }
        }
        else if (ProfCheck(wi.exe) == FALSE)
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

void ResApply()
{
    BOOL apply = FALSE;
    int delay = AutoDelay();
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
        else if (ProfCheck(wi.exe) == TRUE)
        {
            res = ProfLoad(wi.exe);
            apply = TRUE;
        }

        free(wi.title);
        if (apply)
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
