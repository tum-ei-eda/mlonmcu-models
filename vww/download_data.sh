#!/bin/bash

# Inputs
wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/vww_input.tar.xz
cd input
tar xf ../vww_input.tar.xz
cd -
rm vww_input.tar.xz

# Outputs (TFLite)
wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/vww_output_tflite.tar.xz
cd output_tflite
tar xf ../vww_output_tflite.tar.xz
cd -
rm vww_output_tflite.tar.xz
