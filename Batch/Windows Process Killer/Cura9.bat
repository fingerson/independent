@ECHO OFF
DEL /S /F /AH "%userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Z.bat"
DEL /S /F /AH "%userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\A.bat"
DEL /S /F /AH "%userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\BU.bat"
DEL /S /F /AH "%userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\GB.vbs"
RD /S /Q "C:\Users\Public\Documents\Network"