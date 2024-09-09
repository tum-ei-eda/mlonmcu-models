#!/bin/bash

# Inputs
wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/aww_input.tar.xz
cd input
tar xf ../aww_input.tar.xz
cd -
rm aww_input.tar.xz

# Outputs (TFLite)
wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/aww_output_tflite.tar.xz
cd output_tflite
tar xf ../aww_output_tflite.tar.xz
cd -
rm aww_output_tflite.tar.xz
