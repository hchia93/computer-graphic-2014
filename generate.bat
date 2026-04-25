@echo off
setlocal EnableDelayedExpansion

echo ==========================================
echo  computer-graphic-2014 Solution Generator
echo ==========================================
echo.

set "ROOT=%~dp0"
set "ROOT=%ROOT:~0,-1%"

REM 1. Resolve a global vcpkg directory.
REM    Honor VCPKG_ROOT if it is set; otherwise default to C:\vcpkg.
REM    Whatever path we land on will be created and bootstrapped if it
REM    does not already host vcpkg.
if defined VCPKG_ROOT (
    set "VCPKG_DIR=%VCPKG_ROOT%"
) else (
    set "VCPKG_DIR=C:\vcpkg"
)
set "VCPKG_EXE=%VCPKG_DIR%\vcpkg.exe"

REM 2. Ensure vcpkg is cloned at VCPKG_DIR.
if not exist "%VCPKG_DIR%\bootstrap-vcpkg.bat" (
    echo [INFO] vcpkg not found at %VCPKG_DIR%, cloning...
    git --version >nul 2>&1
    if errorlevel 1 (
        echo [ERROR] Git is required to fetch vcpkg. Install from https://git-scm.com/download/win
        pause
        exit /b 1
    )
    git clone https://github.com/microsoft/vcpkg.git "%VCPKG_DIR%"
    if errorlevel 1 (
        echo [ERROR] Failed to clone vcpkg
        pause
        exit /b 1
    )
)
echo [OK] vcpkg present at %VCPKG_DIR%

REM 3. Bootstrap vcpkg.exe if missing.
if not exist "%VCPKG_EXE%" (
    echo [INFO] Bootstrapping vcpkg...
    call "%VCPKG_DIR%\bootstrap-vcpkg.bat" -disableMetrics
    if errorlevel 1 (
        echo [ERROR] Failed to bootstrap vcpkg
        pause
        exit /b 1
    )
)
echo [OK] vcpkg.exe ready

if not defined VCPKG_ROOT (
    echo [HINT] VCPKG_ROOT env var is not set. Consider:
    echo        setx VCPKG_ROOT "%VCPKG_DIR%"
)

REM 4. Detect Visual Studio installation via vswhere.
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo [ERROR] vswhere.exe not found. Install Visual Studio 2017 or newer.
    pause
    exit /b 1
)

set "VS_PATH="
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -prerelease -products * -property installationPath`) do set "VS_PATH=%%i"
if "%VS_PATH%"=="" (
    echo [ERROR] No Visual Studio installation detected.
    pause
    exit /b 1
)

set "VS_VERSION="
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -prerelease -products * -property installationVersion`) do set "VS_VERSION=%%i"
for /f "tokens=1 delims=." %%a in ("%VS_VERSION%") do set "VS_MAJOR=%%a"

set "VS_GENERATOR="
if "%VS_MAJOR%"=="18" set "VS_GENERATOR=Visual Studio 18 2026"
if "%VS_MAJOR%"=="17" set "VS_GENERATOR=Visual Studio 17 2022"
if "%VS_MAJOR%"=="16" set "VS_GENERATOR=Visual Studio 16 2019"
if "%VS_MAJOR%"=="15" set "VS_GENERATOR=Visual Studio 15 2017"

if "%VS_GENERATOR%"=="" (
    echo [ERROR] Unsupported Visual Studio major version: %VS_MAJOR%
    pause
    exit /b 1
)

echo [OK] Visual Studio detected: %VS_PATH% (v%VS_VERSION%)
echo [OK] Using generator: %VS_GENERATOR%

REM 5. Prefer the CMake bundled with the detected Visual Studio,
REM    because it always understands its own generator.
set "CMAKE_EXE=%VS_PATH%\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
if not exist "%CMAKE_EXE%" (
    echo [INFO] VS-bundled cmake not found, falling back to system cmake.
    set "CMAKE_EXE=cmake"
)

REM 6. Generate Visual Studio solution (vcpkg toolchain auto-installs deps
REM    into build\vcpkg_installed\).
if not exist "%ROOT%\build" mkdir "%ROOT%\build"
pushd "%ROOT%\build"
echo [INFO] Generating %VS_GENERATOR% solution (x64)...
"%CMAKE_EXE%" .. -G "%VS_GENERATOR%" -A x64 ^
    -DCMAKE_TOOLCHAIN_FILE="%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake"
if errorlevel 1 (
    echo [ERROR] CMake configuration failed
    popd
    pause
    exit /b 1
)
popd

echo.
echo [SUCCESS] Solution generated under build\
echo  Open the .sln / .slnx in build\ with Visual Studio,
echo  or build from the command line:
echo    "%CMAKE_EXE%" --build build --config Release
echo.
pause
endlocal
