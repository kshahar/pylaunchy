set QTDIR=D:\SDK\qt-win-opensource-src-4.4.0
set PYTHON_ROOT=C:\Python25
set BOOST_1_35_0=D:\SDK\boost\boost_1_35_0

set INNO="C:\Program Files\Inno Setup 5\Compil32.exe"

xcopy /y %BOOST_1_35_0%\lib\boost_python-vc80-mt-1_35.dll tmpbuild

%INNO% /cc PyLaunchy.iss