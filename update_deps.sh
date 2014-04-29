#!/bin/bash

set -x
set -e
set -u

CURRENT_DIR=$(cd `dirname $0`; pwd)

# 1. get poco sources
wget http://pocoproject.org/releases/poco-1.4.6/poco-1.4.6p4.tar.gz

tar zxvf poco-1.4.6p4.tar.gz

cd poco-1.4.6p4

sudo apt-get install libssl-dev

./configure --prefix=$CURRENT_DIR/poco --static --omit=Data/MySQL,Data/ODBC


