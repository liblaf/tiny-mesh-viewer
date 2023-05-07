# Tiny Mesh Viewer

Documentation is hosted on [GitHub](https://liblaf.github.io/tiny-mesh-viewer/).

## Demo

### Phong Shading

![Phong](https://cdn.liblaf.me/github.com/tiny-mesh-viewer/demo/phong.png)

### Gouraud Shading

![Gouraud](https://cdn.liblaf.me/github.com/tiny-mesh-viewer/demo/gouraud.png)

### Results of Deformation Transfer

![Face](https://cdn.liblaf.me/github.com/tiny-mesh-viewer/demo/face.png)

## Build Instructions

### Requirements

#### Required Dependencies

- `C++ Compiler`: C++17 required
- `CMake`
- `vcpkg`

`vcpkg` is bundled in the git submodule. You don't need to download manually. However, you still need to execute `./vcpkg/bootstrap-vcpkg.sh` or `./vcpkg/bootstrap-vcpkg.bat` to initialize `vcpkg`.

#### Optional Dependencies

- `@vercel/serve` (`npm`): to preview HTML documentation in browser
- `black`, `isort` (`pip`): to format python code
- `clang-format`: to format C/C++ code
- `cmakelang` (`pip`): to format CMake files
- `cpplint` (`pip`): to lint C/C++ code
- `doxygen`, `graphviz`: to generate documentation
- `llvm-symbolizer`: used for sanitizers to produce report with symbols
- `requirements.txt` (`pip`): used to generate example sphere mesh

#### My Environment

- `clang-15.0.7`
- `cmake-3.26.3`

### Configuration

You may need to modify these variables in `CMakePresets.json` depending on where the package is installed and the environment:

- `toolchainFile`
- `CC`
- `CXX`

`PRESET` can be configured in `Makefile`, currently supported presets are `debug` (default) and `release`.

There are some other configurable variables, see `debug.cmake`, `lint.cmake` and `sanitizers.cmake` for more details.

### Compile

Simply execute `make` or `make PRESET=release`, and the compilation is complete! The output executable will be located in `build/${PRESET}/source/viewer` and `dist/viewer-*`.

### Preview

See `demo/` for available demos. Note that you don't need to invoke `cmake` directly, the targets can be found in the `Makefile` at the root of the project.

## Usage

### Dependencies

The shader source code files are not required for the program to run, since the shaders are bundled in the executable.

Shared library dependencies may vary by configuration. Here is an example build with default configuration on Linux. (Note that in addition to the system dynamic library, this program also needs OpenMesh to work.)

```shell-session
$ ldd viewer
        linux-vdso.so.1 (0x00007ffcfcfd4000)
        libOpenMeshCore.so.9.0 => build/release/vcpkg_installed/x64-linux/lib/libOpenMeshCore.so.9.0 (0x00007f67ea2e0000)
        libOpenMeshTools.so.9.0 => build/release/vcpkg_installed/x64-linux/lib/libOpenMeshTools.so.9.0 (0x00007f67ea2d0000)
        libm.so.6 => /usr/lib/libm.so.6 (0x00007f67ea1c3000)
        libX11.so.6 => /usr/lib/libX11.so.6 (0x00007f67ea080000)
        libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x00007f67e9e00000)
        libgcc_s.so.1 => /usr/lib/libgcc_s.so.1 (0x00007f67ea05e000)
        libc.so.6 => /usr/lib/libc.so.6 (0x00007f67e9c19000)
        /lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007f67ea5d2000)
        libxcb.so.1 => /usr/lib/libxcb.so.1 (0x00007f67e9bee000)
        libXau.so.6 => /usr/lib/libXau.so.6 (0x00007f67ea059000)
        libXdmcp.so.6 => /usr/lib/libXdmcp.so.6 (0x00007f67ea051000)
```

### Config File

```shell-session
$ viewer --help
A tiny mesh viewer.
Usage:
  viewer [OPTION...]

  -c, --config arg  Config file. (default: config.yaml)
  -h, --help        Show this message and exit.
```

See `demo/full.yaml` for all configurable variables.

#### Change Shader

The rendering of each object depends on the `shaders[*].type`. If you change `shaders[*].id`, make sure to update `scene.objects[*].shader_id` accordingly.

### Camera Control

- `A`: move left
- `S`: move backward
- `D`: move right
- `W`: move forward
- `E`: move upward
- `Q`: move downward
- `ALT` + mouse movement: rotate

## Design

If I merely wanted to complete this assignment, my approach would be too complicated. But I always aim for my code to have some extensibility and maintainability, so I adopted the OOP paradigm at the beginning. However, OpenGL is not designed for OOP, so when I imposed OOP, it resulted in a bit odd program architecture, at least not satisfying. Anyway, as long as it can work in the end, that's fine.

### Directory Structure

- `common`: commonly used utils & helpers
- `opengl`: naive OOP wrapper for OpenGL
- `scene`: 3D scene & lights & objects
- `shader`: shaders extending naive OpenGL wrapper
- `ui`: user interface

> **Note:** The difference between `opengl::Window` and `ui::Window` is that the classes under `opengl::` are only a simple object-oriented wrapper of the OpenGL API, while `ui::` provides a higher level of encapsulation. Classes such as `opengl::Program` and `shader::Shader` have a similar relationship.

### Signal & Slots

![Signal & Slots](https://mermaid.ink/img/pako:eNqVlF1vgjAUhv9K06t96Q8ghsTo5ZaZObMbEnKEg3ST1rRFsjn_-6CWj4K6rTdAeXrO-55z4EAjESP1aLQFpeYMNhKygBNinsk0WzPk-pFtUk0O1T4h90SxDYctiVLgG4xvbqv9Y-fQbteyLzkfADPIUMKf482A70G1-FxCMYCe1-8YNRonk-laaQmR9v3hMZNzKzRZ7WLQuBCKaSaGOheC_df7MkKOv0hdphCj7IRspaw4S4TMBkdeJXtClbYbb4zHojhT5q7GXCohw0zsa6Gdl0nZZ1znSYIyVOwLQ8dRB-RYhAZuRFUXZzDGY5_Urk7Ls6cNWo5Ds-5GI2KL1KCi4Bc4N-RFzhajx9kpOy0jsdNPV-IQvejGDuNpiTNuJJYlRR5hRduprAN_-3Una5rxFCXTcI4XZ2rgRHf8XJftiDRFczrYFG3IObW5wjnSr3C9JljOaaGx0svbWhmivdQXUOum0z6bnT7QMlUGLC7_g-aLCqhOMcOAeuVtDPIjoAE_lhzkWiw_eUQ9LXN8oLn5au1vk3oJbBUefwCU-4zE?type=png)

Each object has a shader reference. The object uses this shader to draw itself when `Object::Draw()` is invoked.

### Call Flow

```cpp
App::Run() -> Window::Run() -> Canvas::Draw() -> Scene::Draw() -> Object::Draw()
```

Refer to [Call Graph](https://liblaf.github.io/tiny-mesh-viewer/dd/df1/classtiny__mesh__viewer_1_1ui_1_1Window.html#ad2143e13c67f3084a1636f831d549fb7) or source code for more intuitive description.

## Implementation

Personally, I am aggressive in embracing modern technologies. I mainly adopted the C++17 standard and [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) to develop this project, and I also applied some features (`source_location`) of C++20 in debug. My code style may differ from others in several aspects, such as:

- avoiding C-style for loops
- detailed inlay hints
- extensive use of lambda expressions
- python-like `with` statement to control OpenGL state
- smart pointers instead of explicit `new`/`delete`

It is actually quite easy to understand the source code, especially with Call Graph, as long as you understand what I explained in the "Design" section. So I will not talk too much nonsense here.
