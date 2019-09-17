#! /bin/sh

clang++ -std=c++17 main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o /tmp/gameoflife && /tmp/gameoflife
