#!/bin/bash

#make clean
make -j 4
mv build/firmware.elf ./casiopy.elf
echo "Finished building firmware; stripping elf"
sh3eb-elf-objcopy -R .comment -R .bss -O binary casiopy.elf casiopy.bin
echo "Wrapping g1a"
g1a-wrapper casiopy.bin -o casiopy.g1a -i icon.bmp
#python g1a-wrapper-fix.py casiopy.g1a