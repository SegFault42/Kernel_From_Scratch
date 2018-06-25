#!/bin/bash

nasm -f elf32 entry.s -o entry.o
gcc -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs -m32 -c main.c -o main.o
ld -m elf_i386 -T link.ld -o /boot/kernel-v0.1 *.o
