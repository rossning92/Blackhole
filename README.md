# Real-time Black Hole Rendering in OpenGL

![Screenshot](docs/blackhole-screenrecord.gif)

## Prerequisite

- [cmake](https://cmake.org/)
- [conan](https://conan.io/) package manager [^1][^2]

[^1]: You might need to configure [$HOME/.conan/conan.conf](https://docs.conan.io/en/latest/reference/config_files/conan.conf.html) and Conan [profiles](https://docs.conan.io/en/latest/reference/profiles.html) if the `default profile` is not generated due to different build environments on your distribution.
[^2]: Conan 1.xx instead of conan 2.xx or higher is suggested in order to avoid unnecessary problems.

## Build the code

```bash
# Configure the project and generate a native build system.
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

# Compile / build the project.
cmake --build build
```

## Acknowledgements

**Papers**

- Gravitational Lensing by Spinning Black Holes in Astrophysics, and in the Movie Interstellar
- Trajectory Around A Spherically Symmetric Non-Rotating Black Hole - Sumanta
- Approximating Light Rays In The Schwarzschild Field - O. Semerak
- Implementing a Rasterization Framework for a Black Hole Spacetime - Yoshiyuki Yamashita

<!-- https://arxiv.org/pdf/1502.03808.pdf -->
<!-- https://arxiv.org/pdf/1109.0676.pdf -->
<!-- https://arxiv.org/pdf/1412.5650.pdf -->
<!-- https://pdfs.semanticscholar.org/56ff/9c575c29ae8ed6042e23075ff0ca00031ccc.pdfhttps://pdfs.semanticscholar.org/56ff/9c575c29ae8ed6042e23075ff0ca00031ccc.pdf -->

**Articles**

- Physics of oseiskar.github.io/black-hole - https://oseiskar.github.io/black-hole/docs/physics.html
- Schwarzschild geodesics - https://en.wikipedia.org/wiki/Schwarzschild_geodesics
- Photons and black holes - https://flannelhead.github.io/posts/2016-03-06-photons-and-black-holes.html
- A real-time simulation of the visual appearance of a Schwarzschild Black Hole - http://spiro.fisica.unipd.it/~antonell/schwarzschild/
- Ray Tracing a Black Hole in C# by Mikolaj Barwicki - https://www.codeproject.com/Articles/994466/Ray-Tracing-a-Black-Hole-in-Csharp
- Ray Marching and Signed Distance Functions - http://jamie-wong.com/2016/07/15/ray-marching-signed-distance-functions/
- Einstein's Rings and the Fabric of Space - https://www.youtube.com/watch?v=Rl8H4XEs0hw)
- Opus 2, GLSL ray tracing tutorial - http://fhtr.blogspot.com/2013/12/opus-2-glsl-ray-tracing-tutorial.html
- Ray Tracing in One Weekend - https://raytracing.github.io/
- On ray casting, ray tracing, ray marching and the like - http://hugi.scene.org/online/hugi37/- hugi%2037%20-%20coding%20adok%20on%20ray%20casting,%20ray%20tracing,%20ray%20marching%20and%20the%20like.htm

**Other GitHub Projects**

- https://github.com/sirxemic/Interstellar
- https://github.com/ssloy/tinyraytracer
- https://github.com/RayTracing/raytracing.github.io
- https://awesomeopensource.com/projects/raytracing
- Ray-traced simulation of a black hole - https://github.com/oseiskar/black-hole
- Raytracing a blackhole - https://rantonels.github.io/starless/
- https://github.com/rantonels/schwarzschild
