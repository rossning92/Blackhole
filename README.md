# Real-time Black Hole Rendering in OpenGL

_(WIP: refactoring, cleaning up and documenting the code)_

![Screenshot](docs/screenshot.jpg)

## Prerequisite

- cmake
- I used [vcpkg](https://github.com/microsoft/vcpkg) to install the following necessary C++ libraries for this project:
  - glew
  - glfw3
  - glm
  - imgui
  - stb

### For windows setup only

- Install `cmake-3.18.3-win64-x64.msi` from this page https://cmake.org/download/
- Install vcpkg:
  - Clone vcpkg repo: `git clone https://github.com/Microsoft/vcpkg.git`
  - Enter vcpkg folder: `cd vcpkg`
  - Build vcpkg: `bootstrap-vcpkg && vcpkg integrate install`
- Install required C++ libs from vcpkg (I've only tested x64 build):
  ```
  vcpkg install glew:x64-windows glfw3:x64-windows glm:x64-windows imgui:x64-windows stb:x64-windows
  ```

#### Build the code

```bash
# Configure the project and generate a native build system. Please replace <vcpkg_dir> with the actual path to your vcpkg folder.
cmake -DCMAKE_TOOLCHAIN_FILE=<vcpkg_dir>/scripts/buildsystems/vcpkg.cmake -S . -B build

# Compile / build the project
cmake --build build
```

### Linux setup and build

- Install CMake and Conan using your distribution's package manager[^1]
- Clone this repo: `git clone https://github.com/rossning92/Blackhole.git`
- Enter this repo's directory `cd Blackhole`
- Make a build directory: `mkdir build`
- Enter the build directory: `cd build`
- Prepare CMake: `cmake .. -DCMAKE_BUILD_TYPE=Release`
- Build: `make`

[^1]: You might need to configure [$HOME/.conan/conan.conf](https://docs.conan.io/en/latest/reference/config_files/conan.conf.html) and Conan [profiles](https://docs.conan.io/en/latest/reference/profiles.html) if the `default profile` is not generated due to different build environments on your distribution.

## Acknowledgements
