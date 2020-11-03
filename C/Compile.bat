@echo off
gcc -Wall -o Run.exe obj/main.o -lfreeglut -lopengl32
PAUSE