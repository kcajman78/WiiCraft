@echo off
TITLE Debugger by JoostinOnline
echo Debugger by JoostinOnline (HacksDen.com)
echo ________________________________________
echo.
echo.
pause

:: Gets the directory that powerpc-eabi-gdb.exe is installed to
setlocal
set devpath=%DEVKITPPC2:/=\%\
set devpath=%devpath:~1,1%:%devpath:~2%
if "%DEVKITPPC2%"=="" (echo DevkitPro is not installed! & goto :eof)

:: If no file was dragged/dropped onto the batch file, use the default filename.
if [%1]==[] goto setdefault

:: Make sure it is an elf file
if not "%~x1" == ".elf" (echo Error: Not an elf file! & goto eof)

:: Set the elf file to what was dragged/dropped onto the bat
set file=%1
goto debug

:setdefault
:: The default file is the name of the folder that Debug.bat is stored in
for %%A in ("%cd%") do set file=%%~nA.elf
set file=%cd%\%file%
:: Make sure it exists, otherwise throw error
if not exist %file% (echo Error: %file% does not exist! & echo Try dragging-and-dropping an elf file onto Debug.bat & goto eof)

:debug
echo Type "info line *0x#", replacing # with the stack dump entry
echo.
echo Example:  info line *0x800a96f8
echo.
echo.
%devpath%powerpc-eabi-gdb.exe %file%


:eof
echo.
echo Press any key to exit...
pause