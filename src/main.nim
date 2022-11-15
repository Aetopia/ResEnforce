import winim/[mean, extra], os, strutils, parsecfg, cpuinfo

proc getForegroundWindowInfo: (string, string, HWND)
proc loadProf(title: string, exe: string): (string, string, string)
proc enforceRes(poll: int)
proc resetRes(poll: int, hwnd: HWND)

proc getForegroundWindowInfo: (string, string, HWND) =
    var 
        pid: DWORD
    let hwnd = GetForegroundWindow()
        
    GetWindowThreadProcessId(hwnd, &pid)
    let
        hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pid) 
        len = GetWindowTextLengthA(hwnd) + 1
        title = newString(len)
        exe = newString(MAX_PATH)
        
    GetWindowTextA(hwnd, title, len)
    GetModuleFileNameExA(hProc, 0, exe, MAX_PATH)
    CloseHandle(hProc)

    return (title.strip(chars={'\0'}), extractFilename(exe).strip(chars={'\0'}), hwnd)   

proc loadProf(title: string, exe: string): (string, string, string) = 
    var res, resT, resE: string
    var file = loadConfig("Options.ini")

    resT = file.getSectionValue("Profiles", title)
    resE = file.getSectionValue("Profiles", exe)

    if (resT != ""): res = resT
    elif (resE != ""): res = resE
    else: res = ""

    return (resT, resE, res)

proc enforceRes(poll: int) = 
    var 
        apply = false
        title, exe, resT, resE, res: string
        dm: seq[string]
        devmode: DEVMODE
        hwnd: HWND
    devmode.dmSize = sizeof(DEVMODE).WORD

    while true:
        (title, exe, hwnd) = getForegroundWindowInfo()
        (resT, resE, res) = loadProf(title, exe)

        if exe == "ApplicationFrameHost.exe":
            if resT != "": apply = true
        elif resE != "": apply = true

        if apply:
            dm = res.split('x')
            (devmode.dmPelsWidth, devmode.dmPelsHeight) = (dm[0].parseInt().DWORD, dm[1].parseInt().DWORD)
            devmode.dmFields = DM_PELSWIDTH or DM_PELSHEIGHT
            ShowWindow(hwnd, SW_RESTORE)
            if ChangeDisplaySettings(&devmode, 0) == DISP_CHANGE_SUCCESSFUL: break
        apply = false
        sleep(poll)

    resetRes(poll, hwnd)

proc resetRes(poll: int, hwnd: HWND) = 
    var 
        reset = false
        title, exe, resT, resE, res: string
        
    while true:
        (title, exe,) = getForegroundWindowInfo()
        (resT, resE, res) = loadProf(title, exe)

        if exe == "ApplicationFrameHost.exe":
            if resT == "": reset = true  
        elif resE == "": reset = true

        if reset:
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE)
            SetForegroundWindow(FindWindow("Shell_TrayWnd", nil))
            if ChangeDisplaySettings(nil, 0) == DISP_CHANGE_SUCCESSFUL: break
        reset = false
        sleep(poll)

    enforceRes(poll)      

if isMainModule:

    # Set the polling rate depending on the amount of CPU threads.
    var poll: int
    case countProcessors():
        of 0..4: poll = 1000
        of 5..7: poll = 100
        else: poll = 1

    # Initialize Resolution Enforcer.
    setCurrentDir(getAppDir())
    if (fileExists("Options.ini") == false):
        writeFile("Options.ini", "[Profiles]\n; Title or Executable Name = Resolution\n; Example.exe = 1600x900\n; Example = 1280x720 \n")
    enforceRes(poll)