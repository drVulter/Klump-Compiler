#!/bin/bash

./Pal_Compiler < $1.pal > $1.asm
echo "Assembling..."
nasm -fmacho32 $1.asm
echo "Linking..."
gcc -arch i386 -Wl -o $1 $1.o
echo "Executing..."
./$1
