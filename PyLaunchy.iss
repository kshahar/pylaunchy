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
#define MyAppVer "0.5.2.0"
#define MyAppURL ""

[Files]
Source: pylaunchy\Release\PyLaunchy.dll; DestDir: {app}\plugins

Source: scripts\skeleton.py; DestDir: {app}\plugins\python; DestName: skeleton.py.RenameToRun
Source: scripts\pyexplorey.py; DestDir: {app}\plugins\python; DestName: pyexplorey.py.RenameToRun
Source: tmpbuild\boost_python-vc80-mt-1_35.dll; DestDir: {app}\

Source: icons\pygo-y.png; DestDir: {app}\plugins\icons
Source: scripts\pygo-y.py; DestDir: {app}\plugins\python
Source: tmpbuild\win32con.py; DestDir: {app}\plugins\python
Source: tmpbuild\win32gui.pyd; DestDir: {app}\plugins\python


[Setup]
AppName={#MyAppName}
AppVerName={#MyAppName} {#MyAppVer}
DefaultDirName={pf}\Launchy
AppPublisher=Shahar Kosti
AppPublisherURL={#MyAppURL}
VersionInfoVersion={#MyAppVer}
OutputBaseFilename=PyLaunchy-0.5.2
OutputDir=.\
AppID={{AD02FF4D-0B7A-480A-AE06-10A2F853CAF3}

[Registry]

