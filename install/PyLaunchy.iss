; Copyright 2008 Shahar Kosti

; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at

     ; http://www.apache.org/licenses/LICENSE-2.0

; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.

#define MyAppName "PyLaunchy"
#define MyAppVer "0.9.0"
#define MyAppURL "http://pylaunchy.sourceforge.net/"

#define RootDir ".."
#define PluginsDir RootDir + "\plugins"
#define SrcDir RootDir + "\src"
#define LicenseFilename "..\license.txt"

#define Exclude ".svn"
#define PluginExclude ".svn, *.png, *.ui, *.ico"

#define PythonSetupFile "python-2.7.msi"
#define PythonUrl "http://www.python.org/download/releases/2.7/"
#define PythonSetupFileUrl "http://python.org/ftp/python/2.7/" + PythonSetupFile
#define PythonRegistryInstallPathKey "SOFTWARE\Python\PythonCore\2.7\InstallPath"

[Files]
; For download and install Python
Source: {#LicenseFilename}; DestDir: {tmp}; BeforeInstall: DownloadInstallPython; Components: Python
Source: tmpbuild\isxdl.dll; Flags: dontcopy

; PyLaunchy core
Source: {#SrcDir}\windows\PyLaunchy\Release\PyLaunchy.dll; DestDir: {app}\plugins; Flags: ignoreversion
Source: tmpbuild\boost_python-vc80-mt-1_41.dll; DestDir: {app}\
Source: icons\pysimple.png; DestDir: {app}\plugins\icons
Source: {#PluginsDir}\pysimple.py; DestDir: {app}\plugins\python\examples
Source: lib\sip.pyd; DestDir: {app}\plugins\python\lib
Source: lib\PyQt4\*.*; DestDir: {app}\plugins\python\lib\PyQt4; Flags: recursesubdirs; Excludes: .svn

; Documentation
Source: {#RootDir}\doc\build\*.*; DestDir: {app}\plugins\python\doc; Flags: recursesubdirs; Excludes: {#Exclude}, *.zip, .doctrees; Components: docs

; PyGo-Y
Source: icons\pygo-y.png; DestDir: {app}\plugins\icons; Components: pygoy
Source: {#PluginsDir}\pygo-y.py; DestDir: {app}\plugins\python; Components: pygoy
Source: lib\win32con.py; DestDir: {app}\plugins\python\lib; Components: pygoy
Source: lib\win32gui.pyd; DestDir: {app}\plugins\python\lib; Components: pygoy
Source: lib\pywintypes27.dll; DestDir: {app}\plugins\python\lib; Components: pygoy

; PyWebIndex
Source: {#PluginsDir}\PyWebIndex\*.*; DestDir: {app}\plugins\python; Flags: recursesubdirs; Excludes: {#PluginExclude}; Components: pywebindex

; PyDiry
Source: {#PluginsDir}\PyDiry\*.*; DestDir: {app}\plugins\python; Flags: recursesubdirs; Excludes: {#PluginExclude}; Components: pydiry
Source: {#PluginsDir}\PyDiry\pydiry.ico; DestDir: {app}\plugins\icons; Components: pydiry

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppName} {#MyAppVer}
DefaultDirName={pf}\Launchy
AppPublisher=
AppPublisherURL={#MyAppURL}
VersionInfoVersion={#MyAppVer}
OutputBaseFilename=PyLaunchy-{#MyAppVer}
OutputDir=.\
; AppID={{AD02FF4D-0B7A-480A-AE06-10A2F853CAF3}
LicenseFile={#LicenseFilename}
DirExistsWarning=no

[Registry]

[Components]
Name: Python; Description: Download and Install Python 2.7; Check: IsPythonMissing; Types: custom full
Name: docs; Description: Documentation; Types: custom full
Name: pygoy; Description: PyGo-y plugin; Types: custom full
Name: pydiry; Description: PyDiry plugin; Types: custom full
Name: pywebindex; Description: PyWebIndex plugin; Types: custom full

[Code]
// isxdl (download using Inno Setup) declerations
function isxdl_Download(hWnd: Integer; URL, Filename: PChar): Integer;
external 'isxdl_Download@files:isxdl.dll stdcall';
function isxdl_SetOption(Option, Value: PChar): Integer;
external 'isxdl_SetOption@files:isxdl.dll stdcall';

// Download and Install Python
procedure DownloadInstallPython();
var wizardHwnd, resultCode: Integer;
begin
	wizardHwnd := StrToInt(ExpandConstant('{wizardhwnd}'))
	isxdl_SetOption('title', 'Downloading Python')

	// Download and execute
	if isxdl_Download(wizardHwnd, '{#PythonSetupFileUrl}', ExpandConstant('{tmp}\{#PythonSetupFile}')) = 1 then begin
		if Exec(ExpandConstant('{tmp}\{#PythonSetupFile}'), '', '', SW_SHOW,ewWaitUntilTerminated, resultCode) then
		begin
			// Success!
			Exit;
		end
	end
	
	// Failed somewhere above
	MsgBox('Download and installation of Python failed. The file can be downloaded at {#PythonUrl}', mbInformation, MB_OK);
	ShellExec('','{#PythonUrl}','','',SW_SHOW,ewNoWait,resultCode);
end;

// Returns true if the correct version of python is not installed
function IsPythonMissing(): Boolean;
begin
	Result := not RegKeyExists(HKLM, '{#PythonRegistryInstallPathKey}');
end;
