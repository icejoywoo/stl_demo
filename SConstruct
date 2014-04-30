#!/bin/env python

import os

env = Environment(CC = "gcc", CXX = "g++", CXXFLAGS = "-Wall -g -O0 -std=c++11")

SConscript(['thirdparty/gmock/SConscript',
            'thirdparty/gtest/SConscript'])

libs = ['pthread', 'gtest', 'gtest_main', 'PocoFoundation', 'PocoNet']
libs_path = ['thirdparty/gtest/lib', 'thirdparty/gmock/lib']
cpp_path = ['thirdparty/gtest/include', 'thirdparty/gmock/include']
# config all code dirs
dirs = ['src', 'src/base', 'src/boost', 'src/poco']

def compile_dir(d):
    for sf in Glob(os.path.join(d, '*.cpp')):
        env.Program(target = sf.name.split('/')[-1][0:-4], 
                    source = [sf], 
                    CPPPATH = [d] + cpp_path + dirs, 
                    LIBS = libs, 
                    LIBPATH = libs_path)

def compile_test(d):
    env.Object(Glob(os.path.join(d, '*_test.cpp')), CPPPATH=[d] + cpp_path + dirs)
    env.Program(target="unittest",
                source=Glob(os.path.join(d, '*_test.o')),
                CPPPATH=[d] + cpp_path + dirs,
                LIBS=libs, LIBPATH=libs_path)

for d in dirs:
    compile_dir(d)

compile_test('test')
