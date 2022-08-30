#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <psapi.h>
#include <ctype.h>

char *GetTitle(HWND hwnd)
{
    int len = GetWindowTextLengthA(hwnd) + 1;
    char *buf = malloc((sizeof(char) * len));
    GetWindowTextA(hwnd, buf, len);
    return buf;
}

char *GetExe(DWORD pid)
{
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    char *buf = malloc((sizeof(char) * MAX_PATH) + 1);
    GetModuleFileNameExA(hProc, NULL, buf, MAX_PATH);
    CloseHandle(hProc);
    return buf;
}

DWORD GetPID(HWND hwnd)
{
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    return pid;
}

char *GetFileExt(char *filepath)
{
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath(filepath, NULL, NULL, fname, ext);
    char *file = malloc((strlen(fname) + strlen(ext)) + 1);
    sprintf(file, "%s%s", fname, ext);
    free(filepath);
    return file;
}

char *GetFileDir(char *filepath)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    _splitpath(filepath, drive, dir, NULL, NULL);
    char *path = malloc((strlen(drive) + strlen(dir)) + 1);
    sprintf(path, "%s%s", drive, dir);
    free(filepath);
    return path;
}