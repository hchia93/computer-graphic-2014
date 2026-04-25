# computer-graphic-2014

Archived university coursework: a 3D model of **St. Basil's Cathedral** (Moscow, Red Square / Kremlin) rendered with C++ and the OpenGL fixed-function pipeline via GLUT.

- **Course:** TGD2151 Computer Graphics Fundamentals / TCS2111 Computer Graphics
- **Session:** Trimester 2, 2014/15
- **Author:** Chia JianFei

## Repository layout

```
.
├── src/         C++ implementation
├── include/     C++ headers
├── bin/         Runtime DLLs (the prebuilt .exe is gitignored)
├── resource/    Texture and asset files used at runtime
│   ├── textures/    Texture sources tested during development
│   └── references/  Reference photographs collected for modelling
├── doc/         Assignment brief, project report, declaration, marking sheet
├── LICENSE      MIT
└── README.md
```

## Tech

- C++ (Code::Blocks / MinGW, circa 2014)
- OpenGL fixed-function pipeline
- GLUT (`glut32.dll`)
- libjpeg (`jpeg62.dll`) for texture loading

## Build

The original Code::Blocks project files were dropped during restructuring because their paths no longer match this layout. A modern build setup (CMake or otherwise) is not yet wired up; this repository is currently kept as an archival snapshot of the original source.

## Status

Cold archive. Kept for personal record.

## License

[MIT](LICENSE)
