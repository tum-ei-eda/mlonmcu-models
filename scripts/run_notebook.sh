#!/bin/sh

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 Notebook.ipynb\n"
    exit 1
fi

. ../../venv/bin/activate

jupyter nbconvert --to notebook --inplace --ExecutePreprocessor.timeout=None --execute "$1"
