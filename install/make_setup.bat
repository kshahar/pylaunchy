set QTDIR=D:\SDK\qt-win-opensource-src-4.4.0
set PYTHON_ROOT=C:\Python25
set BOOST_ROOT=D:\SDK\boost\boost_1_35_0
set BOOST_PYTHON_DLL=%BOOST_ROOT%\lib\boost_python-vc80-mt-1_35.dll

set INNO="%ProgramFiles%\Inno Setup 5\Compil32.exe"

xcopy /y "%BOOST_PYTHON_DLL%" tmpbuild

xcopy /y "%ProgramFiles%\ISTool\isxdl.dll" tmpbuild

%INNO% /cc PyLaunchy.iss