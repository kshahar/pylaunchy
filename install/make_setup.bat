set QTDIR=D:\dev\SDK\qt-everywhere-opensource-src-4.6.0
set PYTHON_ROOT=C:\Python27
set BOOST_ROOT=D:\dev\SDK\boost\boost_1_41_0
set BOOST_PYTHON_DLL=%BOOST_ROOT%\lib\boost_python-vc80-mt-1_41.dll

set INNO="%ProgramFiles(x86)%\Inno Setup 5\Compil32.exe"

mkdir tmpbuild

xcopy /y "%BOOST_PYTHON_DLL%" tmpbuild

xcopy /y "%ProgramFiles(x86)%\ISTool\isxdl.dll" tmpbuild

%INNO% /cc PyLaunchy.iss