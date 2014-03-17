#!/bin/env python

import os

env = Environment(CC = "gcc", CXX = "g++", CXXFLAGS = "-Wall -g -O0")

libs = ['pthread', 'boost_regex', 'boost_signals', 'boost_thread-mt', 'boost_system']
libs_path = []

def compile_dir(d):
    for sf in Glob(os.path.join(d, '*.cpp')):
        env.Program(target = sf.name.split('/')[-1][0:-4], 
                    source = [sf], 
                    CPPPATH = [dir], 
                    LIBS = libs, 
                    LIBPATH = libs_path)

dirs = ['vector']

for d in dirs:
    compile_dir(d)
