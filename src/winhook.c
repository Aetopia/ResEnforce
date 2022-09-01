#include "winhook.h"

DWORD GetWindowPID(HWND hwnd)
{
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    return pid;
}

char *GetWindowTitle(HWND hwnd)
{
    int len = GetWindowTextLengthA(hwnd) + 1;
    char *buf = (char *)malloc(len);
    GetWindowTextA(hwnd, buf, len);
    return buf;
}

char *GetWindowExe(DWORD pid)
{
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    char *buf = (char *)malloc(MAX_PATH + 1);
    GetModuleFileNameExA(hProc, NULL, buf, MAX_PATH);
    CloseHandle(hProc);
    return buf;
}

struct WindowInfo GetForegroundWindowInfo()
{
    HWND hwnd = GetForegroundWindow();
    DWORD pid = GetWindowPID(hwnd);
    char *title = GetWindowTitle(hwnd);
    char *exe = GetWindowExe(pid);
    struct WindowInfo info = {title, exe};
    return info;
}