# ResEnforce
ResEnforce is a rewrite of [Resolution Enforcer](https://github.com/Aetopia/Resolution-Enforcer) but in C instead of Python.

## What is Resolution Enforcer?
A simple program to enforce desktop resolutions on specific applications. (Win32 and UWP apps.)
       
This program fundamentally allows you to force an application to run at a specific resolution of your choice.         
Useful for UWP/Fullscreen Borderless Games since those don't support the ability to use lower resolutions.

# Usage
1. Grab the latest release from [GitHub Releases](https://github.com/Aetopia/ResEnforce/releases).
2. Run `ResEnforce.exe`.
3. This will generate a `Options.ini` file. 
4. Open the file and it should look like this:
   ```ini
   [Profiles]
   ; Title or Executable Name = Resolution
   ; Example.exe = 1600x900
   ; Example = 1280x720 
   ```
5. Adding a new profile is easy:       
    **Note: Executable and title names are case sensitive!**
   1. For Win32 Applications:
      `App.exe = A x B`                    
      Where, `App.exe` is the name of the executable and `A x B` is the resolution to be used.      
      Example: `HaloInfinite.exe = 1600x900`   

   2. For UWP Apps:
      `App Title = A x B`                           
       Where, `App Title` is the name of the UWP App and `A x B` is the resolution to be used.   
       Example: `Minecraft = 1280x720`

6. You end up with:
    ```ini
    [Profiles]
    ; Title or Executable Name = Resolution
   ; Example.exe = 1600x900
   ; Example = 1280x720 
    Minecraft = 1280x720
    HaloInfinite.exe = 1600x900
    ```

7. Simply save the file!

# Building
1. Download the source code and make sure GCC and UPX is installed. (Other compilers will also work.)
   ```powershell
   # You can easily grab them via Scoop.
   scoop.cmd install gcc upx
   ```

2. Run in PowerShell:
   ```powershell
   # Compile ResEnforce.
   gcc src/*.c -mwindows -o ResEnforce.exe

   # Compress the executable.
   upx -9 ResEnforce.exe
   ```