#!/bin/bash
echo "Environment: `uname -a`"
echo "Compiler: `$CXX --version`"

mkdir obj
mkdir lib
make
run-parts ./test/bin
