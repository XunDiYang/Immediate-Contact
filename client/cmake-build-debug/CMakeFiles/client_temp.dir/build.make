# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/xundi/Downloads/clion-2019.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/xundi/Downloads/clion-2019.2.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xundi/github/tem/Immediate-Contact/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xundi/github/tem/Immediate-Contact/client/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/client_temp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client_temp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client_temp.dir/flags.make

CMakeFiles/client_temp.dir/main.cpp.o: CMakeFiles/client_temp.dir/flags.make
CMakeFiles/client_temp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/tem/Immediate-Contact/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client_temp.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_temp.dir/main.cpp.o -c /home/xundi/github/tem/Immediate-Contact/client/main.cpp

CMakeFiles/client_temp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_temp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xundi/github/tem/Immediate-Contact/client/main.cpp > CMakeFiles/client_temp.dir/main.cpp.i

CMakeFiles/client_temp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_temp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xundi/github/tem/Immediate-Contact/client/main.cpp -o CMakeFiles/client_temp.dir/main.cpp.s

CMakeFiles/client_temp.dir/util/cJSON.c.o: CMakeFiles/client_temp.dir/flags.make
CMakeFiles/client_temp.dir/util/cJSON.c.o: ../util/cJSON.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/tem/Immediate-Contact/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/client_temp.dir/util/cJSON.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/client_temp.dir/util/cJSON.c.o   -c /home/xundi/github/tem/Immediate-Contact/client/util/cJSON.c

CMakeFiles/client_temp.dir/util/cJSON.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_temp.dir/util/cJSON.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xundi/github/tem/Immediate-Contact/client/util/cJSON.c > CMakeFiles/client_temp.dir/util/cJSON.c.i

CMakeFiles/client_temp.dir/util/cJSON.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_temp.dir/util/cJSON.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xundi/github/tem/Immediate-Contact/client/util/cJSON.c -o CMakeFiles/client_temp.dir/util/cJSON.c.s

# Object files for target client_temp
client_temp_OBJECTS = \
"CMakeFiles/client_temp.dir/main.cpp.o" \
"CMakeFiles/client_temp.dir/util/cJSON.c.o"

# External object files for target client_temp
client_temp_EXTERNAL_OBJECTS =

client_temp: CMakeFiles/client_temp.dir/main.cpp.o
client_temp: CMakeFiles/client_temp.dir/util/cJSON.c.o
client_temp: CMakeFiles/client_temp.dir/build.make
client_temp: CMakeFiles/client_temp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xundi/github/tem/Immediate-Contact/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable client_temp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_temp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client_temp.dir/build: client_temp

.PHONY : CMakeFiles/client_temp.dir/build

CMakeFiles/client_temp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_temp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_temp.dir/clean

CMakeFiles/client_temp.dir/depend:
	cd /home/xundi/github/tem/Immediate-Contact/client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xundi/github/tem/Immediate-Contact/client /home/xundi/github/tem/Immediate-Contact/client /home/xundi/github/tem/Immediate-Contact/client/cmake-build-debug /home/xundi/github/tem/Immediate-Contact/client/cmake-build-debug /home/xundi/github/tem/Immediate-Contact/client/cmake-build-debug/CMakeFiles/client_temp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client_temp.dir/depend

