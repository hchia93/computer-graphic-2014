# computer-graphic-2014

Archived university coursework: a 3D model of **St. Basil's Cathedral** (Moscow, Red Square / Kremlin) rendered with C++ and the OpenGL fixed-function pipeline via GLUT.

- **Course:** TGD2151 Computer Graphics Fundamentals / TCS2111 Computer Graphics
- **Session:** Trimester 2, 2014/15
- **Author:** Chia JianFei

## Repository layout

```
.
├── CMakeLists.txt    Build script (CMake + vcpkg)
├── vcpkg.json        Manifest of native dependencies
├── generate.bat      One-click solution generator (Windows / Visual Studio)
├── src/              C++ sources and headers
├── bin/Win64/        Build output (gitignored)
├── build/            CMake / Visual Studio generated files, including vcpkg_installed/ (gitignored)
├── resource/         Reference photos and texture sources
│   ├── textures/
│   └── references/
├── doc/              Assignment brief, project report, declaration, marking sheet
├── LICENSE           MIT
└── README.md
```

## Tech

- C++17, MSVC (Visual Studio 2017 / 2019 / 2022 / 2026), x64
- OpenGL fixed-function pipeline
- [freeglut](https://freeglut.sourceforge.net/) via vcpkg (modern drop-in for the original GLUT 3.7)

The original 2014 build used Code::Blocks + MinGW + `glut32.dll` + `jpeg62.dll`. The libjpeg dependency has been dropped because no texture loading code shipped in the final submission.

## Build

Requires Git and Visual Studio 2017 or newer (with the C++ workload). The CMake bundled with Visual Studio is used automatically.

vcpkg is shared across machines via the `VCPKG_ROOT` environment variable; if it is unset, `generate.bat` falls back to `C:\vcpkg`. The chosen directory is cloned and bootstrapped on first run, and reused across every C++ project on the machine afterwards.

```bat
git clone https://github.com/hchia93/computer-graphic-2014.git
cd computer-graphic-2014
generate.bat
```

`generate.bat` will:

1. Resolve a vcpkg location from `VCPKG_ROOT`, falling back to `C:\vcpkg`.
2. Clone and bootstrap vcpkg there if it is not already present.
3. Detect the latest installed Visual Studio via `vswhere` and pick the matching CMake generator.
4. Generate a Visual Studio solution under `build/`. The vcpkg toolchain installs `freeglut` into `build/vcpkg_installed/` during configure.

Build the solution from Visual Studio, or from the command line:

```bat
cmake --build build --config Release
```

The executable lands at `bin/Win64/computer-graphic-2014.exe`. Debug builds also produce `computer-graphic-2014.pdb`.

## License

[MIT](LICENSE)
