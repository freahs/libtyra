#!/bin/bash
echo "Environment: `uname -a`"
echo "Compiler: `$CXX --version`"

make tests
run-parts ./bin/test
