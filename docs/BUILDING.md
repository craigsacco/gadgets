# Gadgets Framework - Building

# Visual Studio

## Requirements

* Visual Studio 2022 (Community Edition will work)
* CMake 3.20 (or newer)
* Clang 17.0 (for code formatting)

## Instructions

Open a **Command Prompt** terminal and run the following commands:

```
> git clone https://github.com/craigsacco/gadgets.git
> cd gadgets
> git submodule init
> git submodule update --init --recursive
> mkdir build-msvc
> cd build-msvc
> cmake -G "Visual Studio 17 2022" ..
```

To open the solution file, double-click the **Gadgets.sln** file from the **build-msvc** folder.

# GCC

## Requirements

* GNU Toolchain (gcc, binutils)
* CMake
* GNU Make
* Clang

### Windows

The following additional requirements is needed:

* MSYS2

For Windows, the packages can be installed with the following commands inside of an **MSYS2** session:
W
```
> pacman -Suy
> pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-make mingw-w64-ucrt-x86_64-clang
```

### Linux

For Ubuntu, the packages can be installed with the following commands in a **bash** session:

```
> sudo apt update
> sudo apt install build-essential cmake g++ gcc clang make
```

## Instructions

Open a **bash** terminal and run the following commands (on Windows, use the UCRT64 shell provided by MSYS):

```
> git clone https://github.com/craigsacco/gadgets.git
> cd gadgets
> git submodule init
> git submodule update --init --recursive
> mkdir build-gcc
> cd build-gcc
> cmake -G "Unix Makefiles" ..
> make -j`nproc`
```
