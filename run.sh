#!/bin/sh

scp -P 2222 segfault42@127.0.0.1:/home/segfault42/Documents/42_KFS1/kernel-v0.1 .
qemu-system-x86_64 -kernel kernel-v0.1
