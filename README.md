# FlatOut 2 Menu Map

Plugin to add a 3D menu map to FlatOut 2

![preview 1](https://i.imgur.com/9q8vmfJ.png)
![preview 2](https://i.imgur.com/WxBKk5f.png)
![preview 3](https://i.imgur.com/9Njo6MJ.png)

## Installation

- Make sure you have v1.2 of the game, as this is the only version this plugin is compatible with. (exe size of 2990080 bytes)
- Plop the files into your game folder, edit `FlatOut2MenuMap_gcp.toml` to change the options to your liking.
- Enjoy, nya~ :3

## LUA functions

For developers, here are the new LUA functions to move the camera and vehicle:

GUI:SetCameraPosition(x, y, z)

GUI:SetCameraTarget(x, y, z)

GUI:SetMenuCarTransform(x1, y1, z1, 0, x2, y2, z2, 0, x3, y3, z3, 0, x4, y4, z4, 1) (this function takes a 4x4 matrix, first 3 pairs are the orientation, then the position)

GUI:SetCameraSplineCount(n)

GUI:SetCameraSplinePoint(i, x, y, z)

GUI:SetCameraSplineSpeed(f)

GUI:Hide3DMenu()

GUI:Show3DMenu()

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
