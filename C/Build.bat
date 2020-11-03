@echo off
del /q /s *.exe
del /q /s *.o
gcc -c src/*.c
move *.o obj
PAUSE