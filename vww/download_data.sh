#!/bin/bash

wget https://syncandshare.lrz.de/dl/fiCKCAjLe8xC99wB1JXNT/validation_data/vww_input.tar.xz
cd input
tar xf ../vww_input.tar.xz
cd -
rm vww_input.tar.xz
