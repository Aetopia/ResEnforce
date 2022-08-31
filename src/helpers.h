#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <psapi.h>
#include <unistd.h>

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