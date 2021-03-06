#!/bin/bash

set -e
set -u
set -x # for debug

scons -Q
if [ $? -ne 0 ]; then
    echo "Failed to build!!!"
    exit -1
fi

./unittest
if [ $? -ne 0 ]; then
    echo "Failed to run unittest!!!"
    exit -1
fi
