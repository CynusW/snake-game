@ECHO OFF

set CONFIG=%1
IF (%CONFIG%=="") DO set CONFIG=Debug

call cmake --build .\.build\ --config "%CONFIG%"