@echo off

set LOCALVARSTEMPLATE=../etc/CUBEmixer/LocalVars.template.bat
set LOCALVARS=../etc/CUBEmixer/LocalVars.bat

REM default values
if exist %LOCALVARSTEMPLATE% (call %LOCALVARSTEMPLATE%)

REM ***** optionally overrides the PD_INSTALL variable *********
if exist %LOCALVARS% (call %LOCALVARS%)

echo starting pd ...
%PD_INSTALL%\pd %GUI_AUDIO% %GUI_MIDI% %GUI_OPTIONS% %PD_OPTIONS% %GUI_PATH% %PD_PATH% %GUI_LIB% %PD_LIB% %GUI_PATCH%
