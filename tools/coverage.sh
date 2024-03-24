#!env bash

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

set -e

# delete all existing coverage data files and outputs
find . -type f -name *.gcda -print0 | xargs -0 rm -f

# execute the unit test runner
pushd build-gcc/src/TestRunner
./GadgetsTestRunner
popd

# generate coverage data
lcov --capture --base-directory . --directory build-gcc/src/ --output /tmp/gadgets_coverage_all.info
lcov --remove /tmp/gadgets_coverage_all.info "/usr/*" "*/ucrt64/*" "*/mingw32/*" "*/mingw64/*" "*/clang32/*" "*/clang64/*" "`pwd`/lib/*" "`pwd`/src/TestRunner/*"  --output /tmp/gadgets_coverage.info

# generate coverage report
rm -rf docs/coverage
mkdir -p docs/coverage
genhtml --branch-coverage /tmp/gadgets_coverage.info --prefix `pwd` --output-directory docs/coverage

# remove coverage data
rm -f /tmp/gadgets_coverage_all.info /tmp/gadgets_coverage.info
