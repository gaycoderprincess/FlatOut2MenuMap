# FlatOut 2 Menu Map

Plugin to add a 3D menu map to FlatOut 2

![preview](https://i.imgur.com/L4uxhJ0.png)

## Installation

- Make sure you have v1.2 of the game, as this is the only version this plugin is compatible with. (exe size of 2990080 bytes)
- Plop the files into your game folder, edit `FlatOut2MenuMap_gcp.toml` to change the options to your liking.
- Enjoy, nya~ :3

## Notes

- This plugin isn't enough for a usable menu map on its own! The game scripts need to be configured to move the car and camera positions accordingly!

## Building

Building is done on an Arch Linux system with CLion and vcpkg being used for the build process. 

Before you begin, clone [nya-common](https://github.com/gaycoderprincess/nya-common) to a folder next to this one, so it can be found.

Required packages: `mingw-w64-gcc vcpkg`

To install all dependencies, use:
```console
vcpkg install tomlplusplus:x86-mingw-static
```

Once installed, copy files from `~/.vcpkg/vcpkg/installed/x86-mingw-static/`:

- `include` dir to `nya-common/3rdparty`
- `lib` dir to `nya-common/lib32`

You should be able to build the project now in CLion.