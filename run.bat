@ECHO OFF

set PLATFORM=%1
IF %PLATFORM% == "" (
    echo Platform is not specified!
    exit /B 0
)

set CONFIG=%2
IF (%CONFIG% == "") DO set CONFIG=Debug

IF NOT EXIST ".bin\%CONFIG%-%PLATFORM%\Snake.exe" (
    call build "%CONFIG%"
    IF %ERRORLEVEL% NEQ 0 (
        exit /B 1
    )

    echo .
    echo .
    echo .
)

set COMMAND="mode CON: COLS=60 LINES=30 && .bin\%CONFIG%-%PLATFORM%\Snake.exe"

start "Snake %CONFIG%-%PLATFORM%" cmd /C %COMMAND%
IF %ERRORLEVEL% NEQ 0 (
    exit /B 2
)

exit /B 0