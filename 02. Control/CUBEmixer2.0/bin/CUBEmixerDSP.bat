@echo off

set LOCALVARSTEMPLATE=../etc/CUBEmixer/LocalVars.template.bat
set LOCALVARS=../etc/CUBEmixer/LocalVars.bat

REM default values
if exist %LOCALVARSTEMPLATE% (call %LOCALVARSTEMPLATE%)

REM ***** optionally overrides the PD_INSTALL variable *********
if exist %LOCALVARS% (call %LOCALVARS%)

echo starting pd ...
%PD_INSTALL%\pd %DSP_AUDIO% %DSP_MIDI% %DSP_OPTIONS% %PD_OPTIONS% %DSP_PATH% %PD_PATH% %DSP_LIB% %PD_LIB% %DSP_PATCH%

