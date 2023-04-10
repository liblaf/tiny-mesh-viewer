# Usage

## Dependencies

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

## Config File

```shell-session
$ viewer --help
A tiny mesh viewer.
Usage:
  viewer [OPTION...]

  -c, --config arg  Config file. (default: config.yaml)
  -h, --help        Show this message and exit.
```

See `demo/full.yaml` for all configurable variables.

## Camera Control

- `A`: move left
- `S`: move backward
- `D`: move right
- `W`: move forward
- `E`: move upward
- `Q`: move downward
- `ALT` + mouse movement: rotate
