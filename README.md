# GTASA-ANTICHEAT-ASI

Anti-Cheat for SA:MP v0.3.7 & v0.3.7-R5 (client mod)

----

## Features

- Anti Car Jacking Exploit

## Description

This anticheat can detect all car jacking. When a car jacking is detected as an exploit, an alert is showed and it is blocked if you are the driver.

The car jacking occurs when a player performs the animation of opening a car door, but the driver doesn't see it and is ejected from the car. That's when SA:MP displays the message "Car Jacked" on the screen. This anticheat detect and show this type of car jacking, but it doesn't show alerts or block it.

Information showed on the screen:
| Field 1 | Field 2 | Field 3 | Field 4 | Field 5 | Field 5 | Field 6 | Field 7 | Field 8 |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| Jacker Name | Driver Name | Teleport Dist | Teleport Up Z | Health | Health Diff | Num. of attempts | Time Elapsed | Show Alert (Exploits) |

## Screenshot

![Screenshot](https://raw.githubusercontent.com/Leonardo541/gtasa-anticheat-asi/refs/heads/main/screenshot.png "Screenshot")

## Configuration

You can change the configuration editing the `samp.cfg` file located in the `GTA San Andreas User Files` folder.

| key | default value | type | description |
| ------ | ------ | ------ | ------ |
| jacked_show_all | 1 | int | Show all players (0 to disable) |
| jacked_max_rows | 10 | int | Max rows of carjackings on screen |
| jacked_position | "48x-320" | string | Position of carjackings on screen |
| jacked_max_time | 99 | int | Max time during which carjackings are showed |
| jacked_examples | 0 | int | Show 3 examples of carjackings (1 to enable) |

The position on screen is based on left / top for positive values ​​and right / bottom for negative values. To apply changes, you need restart the game.

## Supported versions

- SA:MP Client v0.3.7
- SA:MP Client v0.3.7-R5

## How to build

You can compile with Visual Studio 2008 or Mingw-w64

### Visual Studio 2008

**Requirements:**

- Visual Studio 2008
- DirectX 9.0 SDK (Summer 2004)
- [stdint.h](https://github.com/glfw/glfw/blob/cc9168bda1992326e7609d427c4982695455a90a/deps/vs2008/stdint.h)

**How to build:**

* Open `gtasa-anticheat-asi.sln`

### Mingw-w64

**Requirements:**

- mingw-w64-gcc (example: [llvm-mingw](https://github.com/mstorsjo/llvm-mingw/releases))

**How to build:**

- **On Windows:** Open terminal and type `mingw32-make.exe`
- **On Linux:** (cross-compile) Open terminal and type `make`

**Note:**

- You need move all .dll files from `i686-w64-mingw32\bin` folder to `C:\Windows\SysWOW64` folder. Optionally, you can compile statically with `mingw32-make.exe EXTRA_CXXFLAGS=-static` or `make EXTRA_CXXFLAGS=-static`

## How to install

You need to move the `gtasa-anticheat.asi` file to the `GTA San Andreas` folder; you also need `ASI Loader`.
