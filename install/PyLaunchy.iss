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
#define MyAppVer "0.7.6"
#define MyAppURL ""

#define RootDir ".."
#define SrcDir RootDir + "\src"

[Files]
Source: {#SrcDir}\windows\Release\PyLaunchy.dll; DestDir: {app}\plugins
Source: tmpbuild\boost_python-vc80-mt-1_35.dll; DestDir: {app}\
Source: icons\pysimple.png; DestDir: {app}\plugins\icons
Source: {#RootDir}\scripts\pysimple.py; DestDir: {app}\plugins\python\examples
Source: lib\sip.pyd; DestDir: {app}\plugins\python\lib
Source: lib\PyQt4\*.*; DestDir: {app}\plugins\python\lib\PyQt4; Flags: recursesubdirs; Excludes: .svn

Source: {#RootDir}\doc\build\*.*; DestDir: {app}\plugins\python\doc; Flags: recursesubdirs; Excludes: .svn, *.zip; Components: docs

Source: icons\pygo-y.png; DestDir: {app}\plugins\icons; Components: pygoy
Source: {#RootDir}\scripts\pygo-y.py; DestDir: {app}\plugins\python; Components: pygoy
Source: lib\win32con.pyc; DestDir: {app}\plugins\python\lib; Components: pygoy
Source: lib\win32gui.pyd; DestDir: {app}\plugins\python\lib; Components: pygoy
Source: lib\pywintypes25.dll; DestDir: {app}\plugins\python\lib; Components: pygoy

Source: {#RootDir}\scripts\pywebindex.py; DestDir: {app}\plugins\python; Components: pywebindex
Source: {#RootDir}\scripts\pywebindex_ui.py; DestDir: {app}\plugins\python; Components: pywebindex
Source: lib\BeautifulSoup.pyc; DestDir: {app}\plugins\python\lib; Components: pywebindex

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppName} {#MyAppVer}
DefaultDirName={pf}\Launchy
AppPublisher=Shahar Kosti
AppPublisherURL={#MyAppURL}
VersionInfoVersion={#MyAppVer}
OutputBaseFilename=PyLaunchy-{#MyAppVer}
OutputDir=.\
AppID={{AD02FF4D-0B7A-480A-AE06-10A2F853CAF3}
LicenseFile=..\license.txt
DirExistsWarning=no

[Registry]

[Components]
Name: docs; Description: Documentation; Types: custom full
Name: pygoy; Description: PyGo-y plugin; Types: custom full
Name: pywebindex; Description: PyWebIndex plugin; Types: custom full
