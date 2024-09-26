cls

del *.obj
del *.exe
del *.txt

cl.exe /c /EHsc /I..\Include\ *.c 

rc.exe /i ..\Include\ ..\Resource\ogl.rc 
rc.exe /i ..\Include\ text.rc

link *.obj ..\Resource\ogl.res text.res user32.lib gdi32.lib kernel32.lib /OUT:..\bin\%1.exe  /SUBSYSTEM:WINDOWS

del *.obj

..\bin\%1.exe
