#!/bin/sh

dd bs=1 count=2560 if=fulldata.bin of=input/0.bin
dd bs=1 skip=2560 count=2560 if=fulldata.bin of=input/1.bin

python3 ../scripts/convert_data.py float 11.676018 output/0.bin
python3 ../scripts/convert_data.py float 11.001890 output/1.bin
