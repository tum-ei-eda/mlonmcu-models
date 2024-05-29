#!/bin/bash

# Inputs
wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/resnet_input.tar.xz
cd input
tar xf ../resnet_input.tar.xz
cd -
rm resnet_input.tar.xz

# Outputs (TFLite)
wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/resnet_output_tflite.tar.xz
cd output_tflite
tar xf ../resnet_output_tflite.tar.xz
cd -
rm resnet_output_tflite.tar.xz
