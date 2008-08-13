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
#define MyAppVer "0.7.2"
#define MyAppURL ""

[Files]
Source: pylaunchy\Release\PyLaunchy.dll; DestDir: {app}\plugins
Source: tmpbuild\boost_python-vc80-mt-1_35.dll; DestDir: {app}\
Source: tmpbuild\PyQt4\*.*; DestDir: {app}\plugins\python\PyQt4; Flags: recursesubdirs
Source: icons\pysimple.png; DestDir: {app}\plugins\icons
Source: scripts\pysimple.py; DestDir: {app}\plugins\python\examples

Source: icons\pygo-y.png; DestDir: {app}\plugins\icons; Components: pygoy
Source: scripts\pygo-y.py; DestDir: {app}\plugins\python; Components: pygoy
Source: scripts\pygo-y.readme.txt; DestDir: {app}\plugins\python; Components: pygoy
Source: tmpbuild\win32con.py; DestDir: {app}\plugins\python; Components: pygoy
Source: tmpbuild\win32gui.pyd; DestDir: {app}\plugins\python; Components: pygoy

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
LicenseFile=license.txt

[Registry]

[Components]
Name: pygoy; Description: PyGo-y plugin; Types: custom full