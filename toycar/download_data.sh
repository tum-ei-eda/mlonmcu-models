#!/bin/bash

wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/toycar_input.tar.xz
cd input
tar xf ../toycar_input.tar.xz
cd -
rm toycar_input.tar.xz
