# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = "/home/sami/Documents/glfw/Light/material/test 2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/sami/Documents/glfw/Light/material/test 2/build"

# Utility rule file for full_clean.

# Include any custom commands dependencies for this target.
include CMakeFiles/full_clean.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/full_clean.dir/progress.make

CMakeFiles/full_clean:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/home/sami/Documents/glfw/Light/material/test 2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Nettoyage complet du projet."
	/usr/bin/cmake -E rm -rf CMakeFiles main /home/sami/Documents/glfw/Light/material/test\ 2/build/*.o

CMakeFiles/full_clean.dir/codegen:
.PHONY : CMakeFiles/full_clean.dir/codegen

full_clean: CMakeFiles/full_clean
full_clean: CMakeFiles/full_clean.dir/build.make
.PHONY : full_clean

# Rule to build all files generated by this target.
CMakeFiles/full_clean.dir/build: full_clean
.PHONY : CMakeFiles/full_clean.dir/build

CMakeFiles/full_clean.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/full_clean.dir/cmake_clean.cmake
.PHONY : CMakeFiles/full_clean.dir/clean

CMakeFiles/full_clean.dir/depend:
	cd "/home/sami/Documents/glfw/Light/material/test 2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/sami/Documents/glfw/Light/material/test 2" "/home/sami/Documents/glfw/Light/material/test 2" "/home/sami/Documents/glfw/Light/material/test 2/build" "/home/sami/Documents/glfw/Light/material/test 2/build" "/home/sami/Documents/glfw/Light/material/test 2/build/CMakeFiles/full_clean.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/full_clean.dir/depend

