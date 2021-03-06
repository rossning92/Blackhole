# Real-time Black Hole Rendering in OpenGL

_(WIP: refactoring, cleaning up and documenting the code)_

![Screenshot](docs/screenshot.jpg)

## Prerequisite

- cmake
- I used [vcpkg](https://github.com/microsoft/vcpkg) to install the following necessary C++ libraries for this project:
  - glew
  - glfw3
  - glm
  - imgui[opengl3-gl3w-binding]
  - stb

### For windows setup only
- Install `cmake-3.18.3-win64-x64.msi` from this page https://cmake.org/download/
- Install vcpkg:
  - Clone vcpkg repo: `git clone https://github.com/Microsoft/vcpkg.git`
  - Enter vcpkg folder: `cd vcpkg`
  - Build vcpkg: `bootstrap-vcpkg && vcpkg integrate install`
- Install required C++ libs from vcpkg: `vcpkg install glew glfw3 glm imgui[opengl3-gl3w-binding] stb`

## Build the code

```
cmake \
    -DCMAKE_TOOLCHAIN_FILE=<vcpkg_dir>/scripts/buildsystems/vcpkg.cmake \
    -B build -S .
```
(If you are using `cmake-gui`, please make sure the platform is `x86`. `x64` is not tested!)

## Acknowledgements
