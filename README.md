# GTASA-ANTICHEAT-ASI
Anti-Cheat for SA:MP v0.3.7 & v0.3.7-R5 (client mod)

----

## Features

 - Anti Car Jacking Exploit

## Configuration

You can change the configuration in the `samp.cfg` file inside the `GTA San Andreas User Files` folder

## How to build

You can compile with Visual Studio 2008 or Mingw-w64

### Visual Studio 2008

**Requirements:**

- Visual Studio 2008
- DirectX 9.0 SDK (Summer 2004)
- [stdint.h](https://github.com/glfw/glfw/blob/cc9168bda1992326e7609d427c4982695455a90a/deps/vs2008/stdint.h)

**Example:**

Open `gtasa-anticheat-asi.sln`

### Mingw-w64

**Requirements:**

- mingw-w64-gcc (example: [llvm-mingw](https://github.com/mstorsjo/llvm-mingw/releases))

**Example:**

**On Windows:** Open terminal and type `mingw32-make.exe`

**On Linux:** (cross-compile) Open terminal and type `make`

**Note:**

You need move all .dll files from `i686-w64-mingw32\bin` folder to `C:\Windows\SysWOW64` folder. Optionally, you can compile statically with `mingw32-make.exe EXTRA_CXXFLAGS=-static` or `make EXTRA_CXXFLAGS=-static`

## How to install

You need to move the `gtasa-anticheat.asi` file to the `GTA San Andreas` folder; you also need `ASI Loader`.
