#!/bin/sh

scp -P 2222 segfault42@127.0.0.1:/boot/kernel-0.1 .
sudo qemu-system-x86_64 -kernel kernel-v0.1
