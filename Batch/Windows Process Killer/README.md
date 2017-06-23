# /independent/Batch/Windows Process Killer/
This is the Windows Process Killer. The way it works is simple: Each second it searches for a process and sees if it is open.
If the process is open, then it closes it, otherwise, it continues waiting.  
  
HOW TO SET THE FILE UP:  
    * Write the process name down on the line that starts with "SET PROCESS=" on the Windows_Process_Killer file.  
        * The process name can be easily found through the Task Manager.  
    * If you wish to change the name of the "Windows_Process_Killer.bat" file, you might also want to change the last line.  
      Insert there the new name of the file, this way, it should autodelete after setting the other files up (unfortunately, does not always work).  
