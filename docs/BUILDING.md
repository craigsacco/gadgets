# Gadgets Framework - Building

# Windows - Visual Studio

## Requirements

* Visual Studio 2022 (Community Edition will work)
* CMake 3.20 (or newer)
* Clang 17.0 (for code formatting)

## Instructions

* Open a PowerShell or Command Prompt shell and run the following:
    ```
    git clone https://github.com/craigsacco/gadgets.git
    cd gadgets
    mkdir build-msvc
    cd build-msvc
    cmake -G "Visual Studio 17 2022" ..
    ```
* Open the **Gadgets.sln** file from the **build-msvc** folder

# Windows - GCC

## Requirements

* MSYS2 running the UCRT64 shell with the following packages:
    * mingw-w64-ucrt-x86_64-toolchain
    * mingw-w64-ucrt-x86_64-cmake
    * mingw-w64-ucrt-x86_64-make
    * mingw-w64-ucrt-x86_64-clang

## Instructions

Open a UCRT64 shell from MSYS and run the following:

```
git clone https://github.com/craigsacco/gadgets.git
cd gadgets
mkdir build-gcc
cd build-gcc
cmake -G "Unix Makefiles" ..
make -j`nproc`
```
