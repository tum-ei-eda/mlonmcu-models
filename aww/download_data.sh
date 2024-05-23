#!/bin/bash

wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/aww_input.tar.xz
cd output
tar xf ../aww_input.tar.xz
cd -
rm aww_input.tar.xz
