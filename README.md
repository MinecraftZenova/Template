# Mod Template

## Getting Started

### Prerequisites

* **[Visual Studio](https://visualstudio.microsoft.com/downloads/)** - **Make sure to select C++ support in the installer.**
* **[VSNASM](https://github.com/ShiftMediaProject/VSNASM/)**
* **[Python 3](https://www.python.org/downloads/)**
* **[CMake](https://cmake.org/download/)** - ZenovaAPI currently only supports 64-bit

* **Python Packages** - `pip3 install pywin32`

## Changing the Mod Name

**No spaces in the modname**

In the files change Example to your modname

**CMakeLists.txt**
```
set(ModName Example)
```
**resources/modinfo.json**
```
"nameId": "Example"
```

## Building

* Open the CMake GUI app and point the source code to the repository download
* For the build directory, use a build directory inside the source code directory
* Click configure and choose Visual Studio with x64 as the optional platform
* Click finish and then click generate
* Open the solution file in the build folder to open your mod project
* Once you build your files will be put into the proper mod folder in `%zenova_data%/mods/`