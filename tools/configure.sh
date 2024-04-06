#!/usr/bin/env bash

# Copyright (c) 2024 Craig Sacco
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# SPDX-License-Identifier: MIT

set -e

# handle arguments
COMPILER=
CC=
CXX=
COVERAGE=
if [[ $# -gt 2 ]]; then
    echo "Too many arguments"
    exit 1
fi
while [[ $# -gt 0 ]]; do
    case $1 in
        --gcc)
            if [[ "$COMPILER" != "" ]]; then
                echo "Compiler option already specified"
                exit 1
            fi
            COMPILER=gcc
            CC=gcc
            CXX=g++
            shift
            ;;
        --clang)
            if [[ "$COMPILER" != "" ]]; then
                echo "Compiler option already specified"
                exit 1
            fi
            COMPILER=clang
            CC=clang
            CXX=clang++
            shift
            ;;
        --coverage)
            if [[ "$COVERAGE" != "" ]]; then
                echo "Coverage option already specified"
                exit 1
            fi
            COVERAGE=ON
            shift
            ;;
        *)
            echo "Unknown argument: $1"
            exit 1
            ;;
    esac
done

# set default options when not provided
if [[ "$COMPILER" == "" ]]; then
    COMPILER=gcc
    CC=gcc
    CXX=g++
fi
if [[ "$COVERAGE" == "" ]]; then
    COVERAGE=OFF
fi

# configure
mkdir -p build-$COMPILER
pushd build-$COMPILER >> /dev/null
cmake -DCMAKE_C_COMPILER=$CC -DCMAKE_CXX_COMPILER=$CXX -DGADGETS_WITH_COVERAGE=$COVERAGE -G "Unix Makefiles" ..
popd >> /dev/null
