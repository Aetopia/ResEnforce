import winim, os, strutils, parsecfg, cpuinfo

proc getForegroundWindowInfo: (string, string, HWND)
proc loadProf(title: string, exe: string): (string, string, string)
proc enforceRes(delay: int)
proc resetRes(delay: int, hwnd: HWND)

proc getForegroundWindowInfo: (string, string, HWND) =
    var pid: DWORD
    let hwnd = GetForegroundWindow()
    GetWindowThreadProcessId(hwnd, &pid)
    let hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pid)

    let len = GetWindowTextLengthA(hwnd) + 1
    var title = newString(len)
    GetWindowTextA(hwnd, title, len)

    let exe = newString(MAX_PATH)
    GetModuleFileNameExA(hProc, 0, exe, MAX_PATH)
    CloseHandle(hProc)

    return (title.strip(chars={'\0'}), extractFilename(exe).strip(chars={'\0'}), hwnd)   

proc loadProf(title: string, exe: string): (string, string, string) = 
    var res, resT, resE: string
    let file = loadConfig("Options.ini")

    resT = file.getSectionValue("Profiles", title)
    resE = file.getSectionValue("Profiles", exe)

    if (resT != ""): res = resT
    elif (resE != ""): res = resE
    else: res = ""

    return (resT, resE, res)

proc enforceRes(delay: int) = 
    var apply = false
    var title, exe, resT, resE, res: string
    var hwnd: HWND

    while true:
        (title, exe, hwnd) = getForegroundWindowInfo()
        (resT, resE, res) = loadProf(title, exe)
        if exe == "ApplicationFrameHost.exe":
            if resT != "": apply = true
        elif resE != "": apply = true

        if apply:
            var devmode: DEVMODEW
            let dm = res.split('x')
            echo dm
            (devmode.dmPelsWidth, devmode.dmPelsHeight) = (dm[0].parseInt().DWORD, dm[1].parseInt().DWORD)
            devmode.dmFields = DM_PELSWIDTH or DM_PELSHEIGHT
            devmode.dmSize = sizeof(DEVMODEW).WORD
            ChangeDisplaySettings(&devmode, 0)
            break
        sleep(delay)

    resetRes(delay, hwnd)

proc resetRes(delay: int, hwnd: HWND) = 
    var reset = false
    var title, exe, resT, resE, res: string

    while true:
        (title, exe,) = getForegroundWindowInfo()
        (resT, resE, res) = loadProf(title, exe)

        if exe == "ApplicationFrameHost.exe":
            if resT == "": reset = true  
        elif resE == "": reset = true

        if reset and exe in ("ScreenClippingHost.exe") == false:
            ShowWindow(hwnd, SW_FORCEMINIMIZE)
            ChangeDisplaySettings(nil, 0)
            break
        reset = false
        sleep(delay)

    enforceRes(delay)      

if isMainModule:
    var delay: int
    if countProcessors() <= 4: delay = 1000
    else: delay = 100

    setCurrentDir(getAppDir())
    if (fileExists("Options.ini") == false):
        let file = open("Options.ini", fmWrite)
        file.write("[Profiles]\n; Title or Executable Name = Resolution\n; Example.exe = 1600x900\n; Example = 1280x720 \n")
        file.close()
    enforceRes(delay)