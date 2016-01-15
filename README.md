# CMU462 Library

## About

The CMU462 library is designed to build simple graphics applications for
15-462 : Computer Graphics

The library provides basic vector operations, takes care of OpenGL context
creation, window event handling, and an on-screen text display interface using
freetype. The library is designed to provide a simple interface for building
graphics applications and is used in 15-462 assignments.

## Requirements

Freetype is required to build CMU462. CMU462 uses GLFW3 and GLEW for window
management and context creation. Copies of GLEW and GLFW3 are shipped with
the source code and will be compiled from source if they are not installed
on the system.

## Build instruction

Use CMake to generate the build files for your platform as follows:

 * Create a build directory: ```mkdir build ```
 * Configure your build by modifying: ```CMU462/CMakeLists.txt```
 * Run cmake to generate build files: ```cmake ..```
 * And build: ```make```
