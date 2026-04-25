# computer-graphic-2014

![Build Windows Status](https://github.com/hchia93/computer-graphic-2014/actions/workflows/build-windows.yml/badge.svg)

Archived university coursework: a 3D model of **St. Basil's Cathedral** (Moscow, Red Square / Kremlin) rendered with C++ and the OpenGL fixed-function pipeline via GLUT.

- **Course:** TGD2151 Computer Graphics Fundamentals / TCS2111 Computer Graphics
- **Session:** Trimester 2, 2014/15
- **Author:** Chia JianFei

## Repository layout

```
.
├── CMakeLists.txt      Build script
├── CMakePresets.json   Build presets (consumed by VS Open Folder and CLI)
├── vcpkg.json          Manifest of native dependencies
├── src/                C++ sources and headers
├── resource/           Reference photos and texture sources
│   ├── textures/
│   └── references/
├── doc/                Assignment brief, project report, declaration, marking sheet
├── build/              All generated build output (gitignored)
├── LICENSE             MIT
└── README.md
```

## Tech

- C++17, MSVC (Visual Studio 2026), x64
- OpenGL fixed-function pipeline
- [freeglut](https://freeglut.sourceforge.net/) via vcpkg (modern drop-in for the original GLUT 3.7)

Originally built against MinGW with `glut32.dll` and `jpeg62.dll`. The libjpeg dependency has been dropped because no texture loading code shipped in the final submission.

## Build

### Prerequisites

- **Git**
- **Visual Studio 2026** with the C++ workload (the bundled CMake is used; no separate install needed).
- **vcpkg** at any path, exposed via the `VCPKG_ROOT` environment variable. If you do not already have one, clone it once and reuse it across every C++ project on the machine:
  ```bat
  git clone https://github.com/microsoft/vcpkg.git <path>\vcpkg
  <path>\vcpkg\bootstrap-vcpkg.bat -disableMetrics
  setx VCPKG_ROOT <path>\vcpkg
  ```

### First time / clean slate

Run `generate.bat` from a **Visual Studio Developer Command Prompt**. Run it again any time you want a fresh build state.

### Visual Studio

**File → Open → Folder...** → select the repo. Pick `computer-graphic-2014.exe` in the startup-item dropdown, then **F5**.

### Command line

```bat
cmake --build --preset debug
cmake --build --preset release
```

Executable: `build/windows-x64/bin/<Config>/computer-graphic-2014.exe`

## License

[MIT](LICENSE)
