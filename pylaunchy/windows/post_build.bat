REM I don't know how to do post-build events in QT

set SRC="Release\PyLaunchy.dll"
set DST="C:\Program Files\Launchy\plugins\"

taskkill /F /IM Launchy.exe
xcopy /y %SRC% %DST%
