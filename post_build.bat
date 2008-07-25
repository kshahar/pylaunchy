set SRC="Release\PyLaunchy.dll"
set DST="C:\Program Files\Launchy\plugins\"

taskkill /F /IM Launchy.exe
xcopy /y %SRC% %DST%
