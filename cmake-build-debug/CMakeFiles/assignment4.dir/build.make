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
CMAKE_COMMAND = /snap/clion/112/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/112/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/angus/CLionProjects/assignment4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/angus/CLionProjects/assignment4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/assignment4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assignment4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assignment4.dir/flags.make

CMakeFiles/assignment4.dir/main.c.o: CMakeFiles/assignment4.dir/flags.make
CMakeFiles/assignment4.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angus/CLionProjects/assignment4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/assignment4.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assignment4.dir/main.c.o   -c /home/angus/CLionProjects/assignment4/main.c

CMakeFiles/assignment4.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assignment4.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/angus/CLionProjects/assignment4/main.c > CMakeFiles/assignment4.dir/main.c.i

CMakeFiles/assignment4.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assignment4.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/angus/CLionProjects/assignment4/main.c -o CMakeFiles/assignment4.dir/main.c.s

# Object files for target assignment4
assignment4_OBJECTS = \
"CMakeFiles/assignment4.dir/main.c.o"

# External object files for target assignment4
assignment4_EXTERNAL_OBJECTS =

assignment4: CMakeFiles/assignment4.dir/main.c.o
assignment4: CMakeFiles/assignment4.dir/build.make
assignment4: CMakeFiles/assignment4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/angus/CLionProjects/assignment4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable assignment4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assignment4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assignment4.dir/build: assignment4

.PHONY : CMakeFiles/assignment4.dir/build

CMakeFiles/assignment4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assignment4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assignment4.dir/clean

CMakeFiles/assignment4.dir/depend:
	cd /home/angus/CLionProjects/assignment4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/angus/CLionProjects/assignment4 /home/angus/CLionProjects/assignment4 /home/angus/CLionProjects/assignment4/cmake-build-debug /home/angus/CLionProjects/assignment4/cmake-build-debug /home/angus/CLionProjects/assignment4/cmake-build-debug/CMakeFiles/assignment4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/assignment4.dir/depend
