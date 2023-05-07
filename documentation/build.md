# Build Instructions

## Requirements

### Required Dependencies

- `C++ Compiler`: C++17 required
- `CMake`
- `vcpkg`

`vcpkg` is bundled in the git submodule. You don't need to download manually. However, you still need to execute `./vcpkg/bootstrap-vcpkg.sh` or `./vcpkg/bootstrap-vcpkg.bat` to initialize `vcpkg`.

### Optional Dependencies

- `@vercel/serve` (`npm`): to preview HTML documentation in browser
- `black`, `isort` (`pip`): to format python code
- `clang-format`: to format C/C++ code
- `cmakelang` (`pip`): to format CMake files
- `cpplint` (`pip`): to lint C/C++ code
- `doxygen`, `graphviz`: to generate documentation
- `llvm-symbolizer`: used for sanitizers to produce report with symbols
- `requirements.txt` (`pip`): used to generate example sphere mesh

### My Environment

- `clang-15.0.7`
- `cmake-3.26.3`

## Configuration

You may need to modify these variables in `CMakePresets.json` depending on where the package is installed and the environment:

- `toolchainFile`
- `CC`
- `CXX`

`PRESET` can be configured in `Makefile`, currently supported presets are `debug` (default) and `release`.

There are some other configurable variables, see `debug.cmake`, `lint.cmake` and `sanitizers.cmake` for more details.

## Compile

Simply execute `make` or `make PRESET=release`, and the compilation is complete! The output executable will be located in `build/${PRESET}/source/viewer` and `dist/viewer-*`.

## Preview

See `demo/` for available demos. Note that you don't need to invoke `cmake` directly, the targets can be found in the `Makefile` at the root of the project.
