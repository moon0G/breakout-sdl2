@echo off
cmd /k g++ -std=c++17 breakout.cpp -I C:\Users\bfant\Programming\C++\breakout\SDL2\include -L C:\Users\bfant\Programming\C++\breakout\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o breakout
