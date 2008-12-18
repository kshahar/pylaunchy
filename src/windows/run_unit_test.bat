set UnitTest="Release\PyLaunchy.exe"
set DST="C:\Program Files\Launchy\"

xcopy /y %UnitTest% %DST%
pushd %DST%
PyLaunchy.exe --gtest_print_time
popd
pause