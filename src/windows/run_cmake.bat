call set_environment.bat
cmake -D WANT_TEST:BOOL=ON -G "Visual Studio 8 2005" ..\
pause
REM CMAKE_CTEST_COMMAND
