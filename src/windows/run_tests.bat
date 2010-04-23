call set_environment.bat
pushd ..
ctest.exe -V --force-new-ctest-process -C release
popd
pause