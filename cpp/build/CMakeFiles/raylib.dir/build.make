# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wickie/dev/raytracer-challenge/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wickie/dev/raytracer-challenge/cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/raylib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raylib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raylib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raylib.dir/flags.make

CMakeFiles/raylib.dir/src/tuples.cpp.o: CMakeFiles/raylib.dir/flags.make
CMakeFiles/raylib.dir/src/tuples.cpp.o: /home/wickie/dev/raytracer-challenge/cpp/src/tuples.cpp
CMakeFiles/raylib.dir/src/tuples.cpp.o: CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wickie/dev/raytracer-challenge/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raylib.dir/src/tuples.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raylib.dir/src/tuples.cpp.o -MF CMakeFiles/raylib.dir/src/tuples.cpp.o.d -o CMakeFiles/raylib.dir/src/tuples.cpp.o -c /home/wickie/dev/raytracer-challenge/cpp/src/tuples.cpp

CMakeFiles/raylib.dir/src/tuples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raylib.dir/src/tuples.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wickie/dev/raytracer-challenge/cpp/src/tuples.cpp > CMakeFiles/raylib.dir/src/tuples.cpp.i

CMakeFiles/raylib.dir/src/tuples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raylib.dir/src/tuples.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wickie/dev/raytracer-challenge/cpp/src/tuples.cpp -o CMakeFiles/raylib.dir/src/tuples.cpp.s

CMakeFiles/raylib.dir/src/utils.cpp.o: CMakeFiles/raylib.dir/flags.make
CMakeFiles/raylib.dir/src/utils.cpp.o: /home/wickie/dev/raytracer-challenge/cpp/src/utils.cpp
CMakeFiles/raylib.dir/src/utils.cpp.o: CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wickie/dev/raytracer-challenge/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raylib.dir/src/utils.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raylib.dir/src/utils.cpp.o -MF CMakeFiles/raylib.dir/src/utils.cpp.o.d -o CMakeFiles/raylib.dir/src/utils.cpp.o -c /home/wickie/dev/raytracer-challenge/cpp/src/utils.cpp

CMakeFiles/raylib.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raylib.dir/src/utils.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wickie/dev/raytracer-challenge/cpp/src/utils.cpp > CMakeFiles/raylib.dir/src/utils.cpp.i

CMakeFiles/raylib.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raylib.dir/src/utils.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wickie/dev/raytracer-challenge/cpp/src/utils.cpp -o CMakeFiles/raylib.dir/src/utils.cpp.s

# Object files for target raylib
raylib_OBJECTS = \
"CMakeFiles/raylib.dir/src/tuples.cpp.o" \
"CMakeFiles/raylib.dir/src/utils.cpp.o"

# External object files for target raylib
raylib_EXTERNAL_OBJECTS =

libraylib.so: CMakeFiles/raylib.dir/src/tuples.cpp.o
libraylib.so: CMakeFiles/raylib.dir/src/utils.cpp.o
libraylib.so: CMakeFiles/raylib.dir/build.make
libraylib.so: CMakeFiles/raylib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/wickie/dev/raytracer-challenge/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libraylib.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raylib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raylib.dir/build: libraylib.so
.PHONY : CMakeFiles/raylib.dir/build

CMakeFiles/raylib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raylib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raylib.dir/clean

CMakeFiles/raylib.dir/depend:
	cd /home/wickie/dev/raytracer-challenge/cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wickie/dev/raytracer-challenge/cpp /home/wickie/dev/raytracer-challenge/cpp /home/wickie/dev/raytracer-challenge/cpp/build /home/wickie/dev/raytracer-challenge/cpp/build /home/wickie/dev/raytracer-challenge/cpp/build/CMakeFiles/raylib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/raylib.dir/depend
