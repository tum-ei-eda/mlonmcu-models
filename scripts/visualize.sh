#!/bin/sh

# Visualizes the given model in TensorBoard.
# Double click to expand sub-graphs.

set -m

# Args
if [ "$#" -lt 1 ]; then
    echo -e "Usage: $0 ModelName\n"
    exit 1
fi

. ../../venv/bin/activate
PATH_PY2=../../venv/local/lib/python2.7
PATH_PY3=../../venv/lib/python3.6
python $PATH_PY3/site-packages/tensorflow/python/tools/import_pb_to_tensorboard.py --model_dir ../"$1"/"$1".pb --log_dir /tmp/tfboard
tensorboard --logdir /tmp/tfboard &

sleep 1
xdg-open http://localhost:6006

fg
