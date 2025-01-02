; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Approximator"
#define MyAppVersion "2.0"
#define MyAppPublisher "Fire Lizard Software"
#define MyAppURL "http://firelizardsoftware.com/"
#define MyAppExeName "aproxim.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{9BB2FC8B-955F-492A-9447-CB179A9C4470}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=C:\Users\me\Desktop
OutputBaseFilename=aproxim_setup
SetupIconFile=images\sigma.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "release\aproxim.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\libEGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\libGLESv2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt6Charts.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt6DataVisualization.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt6Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\iconengines\*"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release\styles\*"; DestDir: "{app}\styles"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release\translations\*"; DestDir: "{app}\translations"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

