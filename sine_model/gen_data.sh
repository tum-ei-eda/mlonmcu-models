#!/bin/sh

python3 ../scripts/convert_data.py float 0 input/0.bin
python3 ../scripts/convert_data.py float 1.57 input/1.bin
python3 ../scripts/convert_data.py float 3.14 input/2.bin
python3 ../scripts/convert_data.py float 4.71 input/3.bin

python3 ../scripts/convert_data.py hexstr "\x30\x3B\x03\x3D" output/0.bin
python3 ../scripts/convert_data.py hexstr "\x19\xC1\x73\x3F" output/1.bin
python3 ../scripts/convert_data.py hexstr "\x30\x08\x40\xBD" output/2.bin
python3 ../scripts/convert_data.py hexstr "\x54\xB4\x81\xBF" output/3.bin
