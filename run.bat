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

start "Snake %CONFIG%-%PLATFORM%" ".bin\%CONFIG%-%PLATFORM%\Snake.exe"
IF %ERRORLEVEL% NEQ 0 (
    exit /B 2
)

exit /B 0