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
if [[ $# -gt 1 ]]; then
    echo "Too many arguments"
    exit 1
fi
if [[ $# -gt 0 ]]; then
    case $1 in
        --gcc)
            COMPILER=gcc
            shift
            ;;
        *)
            echo "Unknown argument: $1"
            exit 1
            ;;
    esac
fi

# set default options when not provided
if [[ "$COMPILER" == "" ]]; then
    COMPILER=gcc
fi

# run tests with coverage analysis (using gcov/lcov)
if [[ "$COMPILER" == "gcc" ]]; then
    # delete all existing coverage data files and outputs
    find build-gcc/ -type f -name *.gcda -print0 | xargs -0 rm -f

    # generate initial coverage data
    lcov --capture --initial --base-directory . --directory build-gcc/src/ --output ./gadgets_init.lcov.info

    # execute the unit test runner
    pushd build-gcc/src/Tests
    ./GadgetsTestRunner
    popd

    # generate coverage data after running tests
    lcov --capture --base-directory . --directory build-gcc/src/ --output ./gadgets_tests.lcov.info

    # combine the two sets of data, and then strip out the bits we don't need
    lcov --add ./gadgets_init.lcov.info --add ./gadgets_tests.lcov.info --output ./gadgets_all.lcov.info
    lcov --remove ./gadgets_all.lcov.info "/usr/*" "*/ucrt64/*" "*/mingw32/*" "*/mingw64/*" "*/clang32/*" "*/clang64/*" "`pwd`/lib/*" "`pwd`/src/Tests/*" "`pwd`/src/Example/*" --output ./gadgets_filtered.lcov.info

    # generate coverage report
    rm -rf docs/coverage
    mkdir -p docs/coverage
    genhtml ./gadgets_filtered.lcov.info --prefix `pwd` --output-directory docs/coverage
fi
