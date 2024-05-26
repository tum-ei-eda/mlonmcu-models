#!/bin/bash

wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/resnet_input.tar.xz
cd input
tar xf ../resnet_input.tar.xz
cd -
rm resnet_input.tar.xz
