#!/bin/bash

# easier assembly/linkage

nasm -fmacho32 $1.asm
gcc -arch i386 -o $1 $1.o
