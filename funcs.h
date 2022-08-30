#include "helpers.h"
#include "ini.c"
#include <unistd.h>
#include <winuser.h>

struct WindowInfo
{
    char *title;
    char *exe;
    DWORD pid;
};

struct WindowInfo GetForegroundWindowInfo()
{
    HWND hwnd = GetForegroundWindow();
    struct WindowInfo wininfo;
    wininfo.title = GetTitle(hwnd);
    wininfo.exe = GetFileExt(GetExe(GetPID(hwnd)));
    wininfo.pid = GetPID(hwnd);
    return wininfo;
}

void OptionsExist()
{
    if (access("Options.ini", F_OK) == -1)
    {
        FILE *fptr;
        fptr = fopen("Options.ini", "w");
        fprintf(fptr, "[Profiles]\n"
                      "; Title or Executable Name = Resolution\n"
                      "; Example.exe = 1600x900\n"
                      "; Example = 1280x720 \n");
    }
}

BOOL ProfCheck(char *app)
{
    ini_t *ini = ini_load("Options.ini");
    const char *name = ini_get(ini, "Profiles", app);
    if (name != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void ResEnforce()
{
    BOOL apply = FALSE;
    for (;;)
    {
        struct WindowInfo wi = GetForegroundWindowInfo();
        printf("%s | %s\n", wi.title, wi.exe);
        if (ProfCheck(wi.title))
        {
            if (strcmp(wi.exe, "ApplicationFrameHost.exe") == 0)
            {
                break;
            }
        }
        else if (ProfCheck(wi.exe))
        {
            break;
        };

        free(wi.title);
        free(wi.exe);
        Sleep(100);
    }
}