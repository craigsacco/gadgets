#!env bash

find src/ -type f -print0 | xargs -0 dos2unix
find tools/ -type f -print0 | xargs -0 dos2unix
find lib/ -maxdepth 1 -type f -print0 | xargs -0 dos2unix
