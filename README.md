# DownloadManager
CSE 150 project

Welcome to our file manager app! 
before you use this application for the first time you need to configure some things.
By implementing this configuration by yourself, you will be able to fully understand how our file manager app works!

---------------------------------------------------------------------

there are only 3 steps to this setup-

Step 1 :: search "command prompt" on your windows machine, right click then click "Rus as Administrator"
this opens up command prompt with administrative privileges. we need administrative privilege to run our mklink(Symbolic Link command) command.

Step 2 :: now run this 3 commands one by one (press enter after each command)
          
          cd %USERPROFILE%
          ren Downloads realDownloads
          mklink /D %USERPROFILE%\Downloads %USERPROFILE%\realDownloads

the first command takes us to your current user folder, the second command renames your current download folder to "realDownloads"
and the third command creates a symbolic link (named Downloads) to your original downloads folder which is now named realDownloads

Step 3 :: we are done! close the command prompt.


we recommend you create a shortcut to our application (.exe file) in your desktop.

