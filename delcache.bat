@ECHO OFF

IF EXIST .build\CMakeCache.txt (
    del .build\CMakeCache.txt
)