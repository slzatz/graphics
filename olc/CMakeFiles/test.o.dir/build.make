# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/slzatz/graphics/olc/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/slzatz/graphics/olc

# Include any dependencies generated for this target.
include CMakeFiles/test.o.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.o.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.o.dir/flags.make

CMakeFiles/test.o.dir/olcengine3d_obj.cpp.o: CMakeFiles/test.o.dir/flags.make
CMakeFiles/test.o.dir/olcengine3d_obj.cpp.o: src/olcengine3d_obj.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slzatz/graphics/olc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.o.dir/olcengine3d_obj.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.o.dir/olcengine3d_obj.cpp.o -c /home/slzatz/graphics/olc/src/olcengine3d_obj.cpp

CMakeFiles/test.o.dir/olcengine3d_obj.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.o.dir/olcengine3d_obj.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slzatz/graphics/olc/src/olcengine3d_obj.cpp > CMakeFiles/test.o.dir/olcengine3d_obj.cpp.i

CMakeFiles/test.o.dir/olcengine3d_obj.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.o.dir/olcengine3d_obj.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slzatz/graphics/olc/src/olcengine3d_obj.cpp -o CMakeFiles/test.o.dir/olcengine3d_obj.cpp.s

# Object files for target test.o
test_o_OBJECTS = \
"CMakeFiles/test.o.dir/olcengine3d_obj.cpp.o"

# External object files for target test.o
test_o_EXTERNAL_OBJECTS =

test.o: CMakeFiles/test.o.dir/olcengine3d_obj.cpp.o
test.o: CMakeFiles/test.o.dir/build.make
test.o: /usr/lib/libOpenGL.so
test.o: /usr/lib/libGLX.so
test.o: /usr/lib/libSM.so
test.o: /usr/lib/libICE.so
test.o: /usr/lib/libX11.so
test.o: /usr/lib/libXext.so
test.o: /usr/lib/libpng.so
test.o: /usr/lib/libOpenGL.so
test.o: /usr/lib/libz.so
test.o: CMakeFiles/test.o.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/slzatz/graphics/olc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test.o"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.o.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.o.dir/build: test.o

.PHONY : CMakeFiles/test.o.dir/build

CMakeFiles/test.o.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.o.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.o.dir/clean

CMakeFiles/test.o.dir/depend:
	cd /home/slzatz/graphics/olc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/slzatz/graphics/olc/src /home/slzatz/graphics/olc/src /home/slzatz/graphics/olc /home/slzatz/graphics/olc /home/slzatz/graphics/olc/CMakeFiles/test.o.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.o.dir/depend
