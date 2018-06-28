#!/bin/bash
echo "Environment: `uname -a`"
echo "Compiler: `$CXX --version`"

make test
run-parts ./bin/test
