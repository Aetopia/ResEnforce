#include "winhook.h"

struct Window GetForegroundWindowInfo()
{
    DWORD pid;
    struct Window win;
    char *title, *exe = (char *)malloc(MAX_PATH);
    
    HWND hwnd = GetForegroundWindow();
    GetWindowThreadProcessId(hwnd, &pid);
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);

    // Title
    int len = GetWindowTextLengthA(hwnd) + 1;
    title = (char *)malloc(len);
    GetWindowTextA(hwnd, title, len);

    // Executable
    GetModuleFileNameExA(hProc, NULL, exe, MAX_PATH);
    CloseHandle(hProc);

    win.title = title;
    win.exe = basename(exe);
    free(exe);
    return win;
}