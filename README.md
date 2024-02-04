# Window Project
This project involves creating a simple application using the Win32 API to develop a window that centers itself on the screen. Detailed steps and insights into the development process are available on my [website](https://james-door.github.io/cv/projects/window/).

## Building the Project

### Using Visual Studio
The project includes a `CMakePresets.json` file, which is a standard part of the Visual Studio CMake Project template. To build the project in Visual Studio, ensure that **Desktop development with C++** module is installed and the optional **C++ CMake tools for Windows**. Follow these steps:
1. Open the `Win32-Window` folder in Visual Studio.
2. Select `CMakeLists.txt` as the startup item.
3. Visual Studio will automatically handle the build process.

### Without Visual Studio
The Visual Studio method uses Ninja as the generator and Microsoft Visual C++ (MSVC) as the compiler by default. For those who prefer not to use Visual Studio, the project can also be built using other tools. The required steps vary depending on the chosen generator and compiler. Using cmake-gui streamlines the process across different generators, providing a consistent process.

#### Prerequisites
- Install [CMake](https://cmake.org/download/).
- Either use the cmake-gui or command line to configure the build.

#### Building with Ninja and Clang/Clang++
I personally used Ninja along with clang/clang++ compilers for building the project. Some instructions for this method are available in the [Running the Cmake](https://james-door.github.io/cv/projects/window/#Running%20the%20CMake) section on my website.

