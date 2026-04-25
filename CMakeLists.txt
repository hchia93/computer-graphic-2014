cmake_minimum_required(VERSION 3.16)

# Resolve vcpkg toolchain. Prefer the in-tree submodule; fall back to VCPKG_ROOT.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(EXISTS "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
    elseif(DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
    endif()
endif()

project(computer-graphic-2014 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC needs _USE_MATH_DEFINES to expose M_PI from <cmath>.
# GLU is deprecated upstream but still required by the legacy code.
if(MSVC)
    add_compile_definitions(
        _USE_MATH_DEFINES
        _CRT_SECURE_NO_WARNINGS
        GLUT_DISABLE_ATEXIT_HACK
    )
endif()

find_package(FreeGLUT CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES
    src/CGLabmain.cpp
    src/CGProject.cpp
)

set(HEADERS
    include/CGLabmain.h
    include/CGProject.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    FreeGLUT::freeglut
    OpenGL::GL
    OpenGL::GLU
)

# Direct binary and PDB output to bin/Win64, regardless of build configuration.
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/Win64")
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY         "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${OUTPUT_DIR}"
    PDB_OUTPUT_DIRECTORY             "${OUTPUT_DIR}"
    PDB_OUTPUT_DIRECTORY_DEBUG       "${OUTPUT_DIR}"
    PDB_OUTPUT_DIRECTORY_RELEASE     "${OUTPUT_DIR}"
)

if(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY
        VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif()
