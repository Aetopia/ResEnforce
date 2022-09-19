import winim, os, strutils, parsecfg, cpuinfo

proc handler {.noconv.} = quit(1)  
setControlCHook(handler)
proc GetForegroundWindowInfo: (string, string, HWND)
proc OptsExist
proc ProfLoad(title: string, exe: string): (string, string, string)
proc ResEnforce(delay: int)
proc ResReset(delay: int, hwnd: HWND)


proc GetForegroundWindowInfo: (string, string, HWND) =
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

proc OptsExist =
    if (fileExists("Options.ini") == false):
        let file = open("Options.ini", fmWrite)
        file.write("[Profiles]\n; Title or Executable Name = Resolution\n; Example.exe = 1600x900\n; Example = 1280x720 \n")
        file.close()

proc ProfLoad(title: string, exe: string): (string, string, string) = 
    var res, res_t, res_e: string
    let file = loadConfig("Options.ini")

    res_t = file.getSectionValue("Profiles", title)
    res_e = file.getSectionValue("Profiles", exe)

    if (res_t != ""): res = res_t
    elif (res_e != ""): res = res_e
    else: res = ""

    return (res_t, res_e, res)

proc ResEnforce(delay: int) = 
    var apply = false
    var title, exe, res_t, res_e, res: string
    var hwnd: HWND

    while true:
        (title, exe, hwnd) = GetForegroundWindowInfo()
        (res_t, res_e, res) = ProfLoad(title, exe)

        if exe == "ApplicationFrameHost.exe":
            if res_t != "": apply = true
        elif res_e != "": apply = true

        if apply:
            var devmode: DEVMODEW
            let dm = res.split('x')
            (devmode.dmPelsWidth, devmode.dmPelsHeight) = (dm[0].parseInt().DWORD, dm[1].parseInt().DWORD)
            devmode.dmFields = DM_PELSWIDTH or DM_PELSHEIGHT
            devmode.dmSize = sizeof(DEVMODEW).WORD
            ChangeDisplaySettings(&devmode, 0)
            break
        sleep(delay)

    ResReset(delay, hwnd)

proc ResReset(delay: int, hwnd: HWND) = 
    var reset = false
    var title, exe, res_t, res_e, res: string

    while true:
        (title, exe,) = GetForegroundWindowInfo()
        (res_t, res_e, res) = ProfLoad(title, exe)

        if exe == "ApplicationFrameHost.exe":
            if res_t == "": reset = true  
        elif res_e == "": reset = true

        if reset:
            ShowWindow(hwnd, SW_SHOWMINNOACTIVE)
            ChangeDisplaySettings(nil, 0)
            break
        sleep(delay)

    ResEnforce(delay)      

if isMainModule:
    var delay: int
    let cpucount = countProcessors()
    if cpucount <= 4: delay = 1000
    else: delay = 100

    setCurrentDir(splitpath(getAppFilename())[0])
    OptsExist()
    ResEnforce(delay)
