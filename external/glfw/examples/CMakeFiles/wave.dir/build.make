# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw

# Include any dependencies generated for this target.
include examples/CMakeFiles/wave.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/wave.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/wave.dir/flags.make

examples/CMakeFiles/wave.dir/wave.c.o: examples/CMakeFiles/wave.dir/flags.make
examples/CMakeFiles/wave.dir/wave.c.o: examples/wave.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/wave.dir/wave.c.o"
	cd /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples && /usr/lib64/ccache/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/wave.dir/wave.c.o   -c /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples/wave.c

examples/CMakeFiles/wave.dir/wave.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wave.dir/wave.c.i"
	cd /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples && /usr/lib64/ccache/cc  $(C_DEFINES) $(C_FLAGS) -E /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples/wave.c > CMakeFiles/wave.dir/wave.c.i

examples/CMakeFiles/wave.dir/wave.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wave.dir/wave.c.s"
	cd /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples && /usr/lib64/ccache/cc  $(C_DEFINES) $(C_FLAGS) -S /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples/wave.c -o CMakeFiles/wave.dir/wave.c.s

examples/CMakeFiles/wave.dir/wave.c.o.requires:
.PHONY : examples/CMakeFiles/wave.dir/wave.c.o.requires

examples/CMakeFiles/wave.dir/wave.c.o.provides: examples/CMakeFiles/wave.dir/wave.c.o.requires
	$(MAKE) -f examples/CMakeFiles/wave.dir/build.make examples/CMakeFiles/wave.dir/wave.c.o.provides.build
.PHONY : examples/CMakeFiles/wave.dir/wave.c.o.provides

examples/CMakeFiles/wave.dir/wave.c.o.provides.build: examples/CMakeFiles/wave.dir/wave.c.o

# Object files for target wave
wave_OBJECTS = \
"CMakeFiles/wave.dir/wave.c.o"

# External object files for target wave
wave_EXTERNAL_OBJECTS =

examples/wave: examples/CMakeFiles/wave.dir/wave.c.o
examples/wave: examples/CMakeFiles/wave.dir/build.make
examples/wave: src/libglfw3.a
examples/wave: /usr/lib64/libGLU.so
examples/wave: /usr/lib64/libX11.so
examples/wave: /usr/lib64/librt.so
examples/wave: /usr/lib64/libXrandr.so
examples/wave: /usr/lib64/libXinerama.so
examples/wave: /usr/lib64/libXi.so
examples/wave: /usr/lib64/libXxf86vm.so
examples/wave: /usr/lib64/librt.so
examples/wave: /usr/lib64/libm.so
examples/wave: /usr/lib64/libXcursor.so
examples/wave: /usr/lib64/libGL.so
examples/wave: /usr/lib64/libXrandr.so
examples/wave: /usr/lib64/libXinerama.so
examples/wave: /usr/lib64/libXi.so
examples/wave: /usr/lib64/libXxf86vm.so
examples/wave: /usr/lib64/libm.so
examples/wave: /usr/lib64/libXcursor.so
examples/wave: /usr/lib64/libGL.so
examples/wave: examples/CMakeFiles/wave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable wave"
	cd /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/wave.dir/build: examples/wave
.PHONY : examples/CMakeFiles/wave.dir/build

examples/CMakeFiles/wave.dir/requires: examples/CMakeFiles/wave.dir/wave.c.o.requires
.PHONY : examples/CMakeFiles/wave.dir/requires

examples/CMakeFiles/wave.dir/clean:
	cd /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/wave.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/wave.dir/clean

examples/CMakeFiles/wave.dir/depend:
	cd /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples /afs/andrew.cmu.edu/usr20/shuangg/Desktop/462/libCSD462/external/glfw/examples/CMakeFiles/wave.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/wave.dir/depend

