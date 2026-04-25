cmake_minimum_required(VERSION 3.25)

project(computer-graphic-2014 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC needs _USE_MATH_DEFINES to expose M_PI from <cmath>; the legacy
# code also predates the deprecation noise around GLU.
if(MSVC)
    add_compile_definitions(
        _USE_MATH_DEFINES
        _CRT_SECURE_NO_WARNINGS
        GLUT_DISABLE_ATEXIT_HACK
    )
endif()

find_package(FreeGLUT CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    src/CGLabmain.cpp
    src/CGProject.cpp
)

set(HEADERS
    src/CGLabmain.h
    src/CGProject.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    FreeGLUT::freeglut
    OpenGL::GL
    OpenGL::GLU
)

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endif()
