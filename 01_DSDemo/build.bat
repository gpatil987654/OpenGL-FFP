cls

del *.obj
del *.exe
del *.txt

cl.exe /c /EHsc  *.c 

rc.exe ogl.rc 

link *.obj ogl.res user32.lib gdi32.lib kernel32.lib /OUT:%1.exe  /SUBSYSTEM:WINDOWS

del *.obj

%1.exe
