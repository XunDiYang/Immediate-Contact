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
CMAKE_SOURCE_DIR = /home/xundi/github/seven_chat/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xundi/github/seven_chat/server

# Include any dependencies generated for this target.
include include/CMakeFiles/Database_server.dir/depend.make

# Include the progress variables for this target.
include include/CMakeFiles/Database_server.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/Database_server.dir/flags.make

include/CMakeFiles/Database_server.dir/friends.cpp.o: include/CMakeFiles/Database_server.dir/flags.make
include/CMakeFiles/Database_server.dir/friends.cpp.o: include/friends.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/seven_chat/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/CMakeFiles/Database_server.dir/friends.cpp.o"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Database_server.dir/friends.cpp.o -c /home/xundi/github/seven_chat/server/include/friends.cpp

include/CMakeFiles/Database_server.dir/friends.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Database_server.dir/friends.cpp.i"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xundi/github/seven_chat/server/include/friends.cpp > CMakeFiles/Database_server.dir/friends.cpp.i

include/CMakeFiles/Database_server.dir/friends.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Database_server.dir/friends.cpp.s"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xundi/github/seven_chat/server/include/friends.cpp -o CMakeFiles/Database_server.dir/friends.cpp.s

include/CMakeFiles/Database_server.dir/gmessage.cpp.o: include/CMakeFiles/Database_server.dir/flags.make
include/CMakeFiles/Database_server.dir/gmessage.cpp.o: include/gmessage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/seven_chat/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object include/CMakeFiles/Database_server.dir/gmessage.cpp.o"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Database_server.dir/gmessage.cpp.o -c /home/xundi/github/seven_chat/server/include/gmessage.cpp

include/CMakeFiles/Database_server.dir/gmessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Database_server.dir/gmessage.cpp.i"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xundi/github/seven_chat/server/include/gmessage.cpp > CMakeFiles/Database_server.dir/gmessage.cpp.i

include/CMakeFiles/Database_server.dir/gmessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Database_server.dir/gmessage.cpp.s"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xundi/github/seven_chat/server/include/gmessage.cpp -o CMakeFiles/Database_server.dir/gmessage.cpp.s

include/CMakeFiles/Database_server.dir/group.cpp.o: include/CMakeFiles/Database_server.dir/flags.make
include/CMakeFiles/Database_server.dir/group.cpp.o: include/group.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/seven_chat/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object include/CMakeFiles/Database_server.dir/group.cpp.o"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Database_server.dir/group.cpp.o -c /home/xundi/github/seven_chat/server/include/group.cpp

include/CMakeFiles/Database_server.dir/group.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Database_server.dir/group.cpp.i"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xundi/github/seven_chat/server/include/group.cpp > CMakeFiles/Database_server.dir/group.cpp.i

include/CMakeFiles/Database_server.dir/group.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Database_server.dir/group.cpp.s"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xundi/github/seven_chat/server/include/group.cpp -o CMakeFiles/Database_server.dir/group.cpp.s

include/CMakeFiles/Database_server.dir/message.cpp.o: include/CMakeFiles/Database_server.dir/flags.make
include/CMakeFiles/Database_server.dir/message.cpp.o: include/message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/seven_chat/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object include/CMakeFiles/Database_server.dir/message.cpp.o"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Database_server.dir/message.cpp.o -c /home/xundi/github/seven_chat/server/include/message.cpp

include/CMakeFiles/Database_server.dir/message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Database_server.dir/message.cpp.i"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xundi/github/seven_chat/server/include/message.cpp > CMakeFiles/Database_server.dir/message.cpp.i

include/CMakeFiles/Database_server.dir/message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Database_server.dir/message.cpp.s"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xundi/github/seven_chat/server/include/message.cpp -o CMakeFiles/Database_server.dir/message.cpp.s

include/CMakeFiles/Database_server.dir/section.cpp.o: include/CMakeFiles/Database_server.dir/flags.make
include/CMakeFiles/Database_server.dir/section.cpp.o: include/section.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/seven_chat/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object include/CMakeFiles/Database_server.dir/section.cpp.o"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Database_server.dir/section.cpp.o -c /home/xundi/github/seven_chat/server/include/section.cpp

include/CMakeFiles/Database_server.dir/section.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Database_server.dir/section.cpp.i"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xundi/github/seven_chat/server/include/section.cpp > CMakeFiles/Database_server.dir/section.cpp.i

include/CMakeFiles/Database_server.dir/section.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Database_server.dir/section.cpp.s"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xundi/github/seven_chat/server/include/section.cpp -o CMakeFiles/Database_server.dir/section.cpp.s

include/CMakeFiles/Database_server.dir/user.cpp.o: include/CMakeFiles/Database_server.dir/flags.make
include/CMakeFiles/Database_server.dir/user.cpp.o: include/user.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/seven_chat/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object include/CMakeFiles/Database_server.dir/user.cpp.o"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Database_server.dir/user.cpp.o -c /home/xundi/github/seven_chat/server/include/user.cpp

include/CMakeFiles/Database_server.dir/user.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Database_server.dir/user.cpp.i"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xundi/github/seven_chat/server/include/user.cpp > CMakeFiles/Database_server.dir/user.cpp.i

include/CMakeFiles/Database_server.dir/user.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Database_server.dir/user.cpp.s"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xundi/github/seven_chat/server/include/user.cpp -o CMakeFiles/Database_server.dir/user.cpp.s

include/CMakeFiles/Database_server.dir/userGroup.cpp.o: include/CMakeFiles/Database_server.dir/flags.make
include/CMakeFiles/Database_server.dir/userGroup.cpp.o: include/userGroup.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xundi/github/seven_chat/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object include/CMakeFiles/Database_server.dir/userGroup.cpp.o"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Database_server.dir/userGroup.cpp.o -c /home/xundi/github/seven_chat/server/include/userGroup.cpp

include/CMakeFiles/Database_server.dir/userGroup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Database_server.dir/userGroup.cpp.i"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xundi/github/seven_chat/server/include/userGroup.cpp > CMakeFiles/Database_server.dir/userGroup.cpp.i

include/CMakeFiles/Database_server.dir/userGroup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Database_server.dir/userGroup.cpp.s"
	cd /home/xundi/github/seven_chat/server/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xundi/github/seven_chat/server/include/userGroup.cpp -o CMakeFiles/Database_server.dir/userGroup.cpp.s

# Object files for target Database_server
Database_server_OBJECTS = \
"CMakeFiles/Database_server.dir/friends.cpp.o" \
"CMakeFiles/Database_server.dir/gmessage.cpp.o" \
"CMakeFiles/Database_server.dir/group.cpp.o" \
"CMakeFiles/Database_server.dir/message.cpp.o" \
"CMakeFiles/Database_server.dir/section.cpp.o" \
"CMakeFiles/Database_server.dir/user.cpp.o" \
"CMakeFiles/Database_server.dir/userGroup.cpp.o"

# External object files for target Database_server
Database_server_EXTERNAL_OBJECTS =

include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/friends.cpp.o
include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/gmessage.cpp.o
include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/group.cpp.o
include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/message.cpp.o
include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/section.cpp.o
include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/user.cpp.o
include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/userGroup.cpp.o
include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/build.make
include/libDatabase_server.a: include/CMakeFiles/Database_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xundi/github/seven_chat/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libDatabase_server.a"
	cd /home/xundi/github/seven_chat/server/include && $(CMAKE_COMMAND) -P CMakeFiles/Database_server.dir/cmake_clean_target.cmake
	cd /home/xundi/github/seven_chat/server/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Database_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/Database_server.dir/build: include/libDatabase_server.a

.PHONY : include/CMakeFiles/Database_server.dir/build

include/CMakeFiles/Database_server.dir/clean:
	cd /home/xundi/github/seven_chat/server/include && $(CMAKE_COMMAND) -P CMakeFiles/Database_server.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/Database_server.dir/clean

include/CMakeFiles/Database_server.dir/depend:
	cd /home/xundi/github/seven_chat/server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xundi/github/seven_chat/server /home/xundi/github/seven_chat/server/include /home/xundi/github/seven_chat/server /home/xundi/github/seven_chat/server/include /home/xundi/github/seven_chat/server/include/CMakeFiles/Database_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/CMakeFiles/Database_server.dir/depend

