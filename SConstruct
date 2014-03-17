#!/bin/env python

import os

env = Environment(CC = "gcc", CXX = "g++", CXXFLAGS = "-Wall -g -O0")

env.SConscript('thirdparty/gmock/SConscript')
env.SConscript('thirdparty/gtest/SConscript')

libs = ['pthread', 'gtest', 'gtest_main']
libs_path = ['thirdparty/gtest/lib', 'thirdparty/gmock/lib']
cpp_path = ['thirdparty/gtest/include', 'thirdparty/gmock/include']

def compile_dir(d):
    for sf in Glob(os.path.join(d, '*.cpp')):
        env.Program(target = sf.name.split('/')[-1][0:-4], 
                    source = [sf], 
                    CPPPATH = [dir] + cpp_path, 
                    LIBS = libs, 
                    LIBPATH = libs_path)

dirs = ['src', 'test']

for d in dirs:
    compile_dir(d)
