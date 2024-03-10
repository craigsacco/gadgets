#!env bash

find src/ -type f -iname *.cpp -print0 | xargs -0 clang-format -i
find src/ -type f -iname *.hpp -print0 | xargs -0 clang-format -i