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
├── vcpkg/            vcpkg toolchain (git submodule)
├── src/              C++ implementation
├── include/          C++ headers
├── bin/
│   ├── Win64/          Build output (gitignored)
│   ├── legacy/         Original 2014 runtime DLLs (glut32, jpeg62)
│   └── CGLabs.exe      Original 2014 prebuilt binary (gitignored)
├── resource/         Reference photos and texture sources
│   ├── textures/
│   └── references/
├── doc/              Assignment brief, project report, declaration, marking sheet
├── LICENSE           MIT
└── README.md
```

## Tech

- C++17, MSVC (Visual Studio 2022), x64
- OpenGL fixed-function pipeline
- [freeglut](https://freeglut.sourceforge.net/) via vcpkg (modern drop-in for the original GLUT 3.7)

The original 2014 build used Code::Blocks + MinGW + `glut32.dll` + `jpeg62.dll`. The legacy DLLs are kept under `bin/legacy/` for reference; the project no longer depends on libjpeg because no texture loading code shipped in the final submission.

## Build

Requires Git, Visual Studio 2022 (with the C++ workload), and CMake.

```bat
git clone --recurse-submodules https://github.com/hchia93/computer-graphic-2014.git
cd computer-graphic-2014
generate.bat
```

`generate.bat` will:

1. Initialise the `vcpkg` submodule if needed.
2. Bootstrap `vcpkg.exe` if missing.
3. Install manifest dependencies (`freeglut`) for the `x64-windows` triplet.
4. Generate a Visual Studio 2022 solution under `generated-vs/`.

Build the solution from Visual Studio, or from the command line:

```bat
cmake --build generated-vs --config Release
```

The executable lands at `bin/Win64/computer-graphic-2014.exe` along with its `.pdb`.

## License

[MIT](LICENSE)
