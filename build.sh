#!/bin/bash

scons -Q
if [ $? -ne 0 ]; then
    echo "Failed to build!!!"
    exit -1
fi

./stl_unittest
if [ $? -ne 0 ]; then
    echo "Failed to run unittest!!!"
    exit -1
fi
