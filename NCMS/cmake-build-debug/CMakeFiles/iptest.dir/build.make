# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/CLionProjects/iptest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/CLionProjects/iptest/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/iptest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/iptest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/iptest.dir/flags.make

CMakeFiles/iptest.dir/main.c.o: CMakeFiles/iptest.dir/flags.make
CMakeFiles/iptest.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/iptest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/iptest.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iptest.dir/main.c.o   -c /root/CLionProjects/iptest/main.c

CMakeFiles/iptest.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iptest.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/iptest/main.c > CMakeFiles/iptest.dir/main.c.i

CMakeFiles/iptest.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iptest.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/iptest/main.c -o CMakeFiles/iptest.dir/main.c.s

CMakeFiles/iptest.dir/log_queue.c.o: CMakeFiles/iptest.dir/flags.make
CMakeFiles/iptest.dir/log_queue.c.o: ../log_queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/iptest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/iptest.dir/log_queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iptest.dir/log_queue.c.o   -c /root/CLionProjects/iptest/log_queue.c

CMakeFiles/iptest.dir/log_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iptest.dir/log_queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/iptest/log_queue.c > CMakeFiles/iptest.dir/log_queue.c.i

CMakeFiles/iptest.dir/log_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iptest.dir/log_queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/iptest/log_queue.c -o CMakeFiles/iptest.dir/log_queue.c.s

CMakeFiles/iptest.dir/data_queue.c.o: CMakeFiles/iptest.dir/flags.make
CMakeFiles/iptest.dir/data_queue.c.o: ../data_queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/iptest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/iptest.dir/data_queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iptest.dir/data_queue.c.o   -c /root/CLionProjects/iptest/data_queue.c

CMakeFiles/iptest.dir/data_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iptest.dir/data_queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/iptest/data_queue.c > CMakeFiles/iptest.dir/data_queue.c.i

CMakeFiles/iptest.dir/data_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iptest.dir/data_queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/iptest/data_queue.c -o CMakeFiles/iptest.dir/data_queue.c.s

CMakeFiles/iptest.dir/http_hash.c.o: CMakeFiles/iptest.dir/flags.make
CMakeFiles/iptest.dir/http_hash.c.o: ../http_hash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/iptest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/iptest.dir/http_hash.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iptest.dir/http_hash.c.o   -c /root/CLionProjects/iptest/http_hash.c

CMakeFiles/iptest.dir/http_hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iptest.dir/http_hash.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/iptest/http_hash.c > CMakeFiles/iptest.dir/http_hash.c.i

CMakeFiles/iptest.dir/http_hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iptest.dir/http_hash.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/iptest/http_hash.c -o CMakeFiles/iptest.dir/http_hash.c.s

CMakeFiles/iptest.dir/actrie.c.o: CMakeFiles/iptest.dir/flags.make
CMakeFiles/iptest.dir/actrie.c.o: ../actrie.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/iptest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/iptest.dir/actrie.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iptest.dir/actrie.c.o   -c /root/CLionProjects/iptest/actrie.c

CMakeFiles/iptest.dir/actrie.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iptest.dir/actrie.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/iptest/actrie.c > CMakeFiles/iptest.dir/actrie.c.i

CMakeFiles/iptest.dir/actrie.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iptest.dir/actrie.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/iptest/actrie.c -o CMakeFiles/iptest.dir/actrie.c.s

CMakeFiles/iptest.dir/change.c.o: CMakeFiles/iptest.dir/flags.make
CMakeFiles/iptest.dir/change.c.o: ../change.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CLionProjects/iptest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/iptest.dir/change.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iptest.dir/change.c.o   -c /root/CLionProjects/iptest/change.c

CMakeFiles/iptest.dir/change.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iptest.dir/change.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/CLionProjects/iptest/change.c > CMakeFiles/iptest.dir/change.c.i

CMakeFiles/iptest.dir/change.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iptest.dir/change.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/CLionProjects/iptest/change.c -o CMakeFiles/iptest.dir/change.c.s

# Object files for target iptest
iptest_OBJECTS = \
"CMakeFiles/iptest.dir/main.c.o" \
"CMakeFiles/iptest.dir/log_queue.c.o" \
"CMakeFiles/iptest.dir/data_queue.c.o" \
"CMakeFiles/iptest.dir/http_hash.c.o" \
"CMakeFiles/iptest.dir/actrie.c.o" \
"CMakeFiles/iptest.dir/change.c.o"

# External object files for target iptest
iptest_EXTERNAL_OBJECTS =

iptest: CMakeFiles/iptest.dir/main.c.o
iptest: CMakeFiles/iptest.dir/log_queue.c.o
iptest: CMakeFiles/iptest.dir/data_queue.c.o
iptest: CMakeFiles/iptest.dir/http_hash.c.o
iptest: CMakeFiles/iptest.dir/actrie.c.o
iptest: CMakeFiles/iptest.dir/change.c.o
iptest: CMakeFiles/iptest.dir/build.make
iptest: CMakeFiles/iptest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CLionProjects/iptest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable iptest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iptest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/iptest.dir/build: iptest

.PHONY : CMakeFiles/iptest.dir/build

CMakeFiles/iptest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/iptest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/iptest.dir/clean

CMakeFiles/iptest.dir/depend:
	cd /root/CLionProjects/iptest/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CLionProjects/iptest /root/CLionProjects/iptest /root/CLionProjects/iptest/cmake-build-debug /root/CLionProjects/iptest/cmake-build-debug /root/CLionProjects/iptest/cmake-build-debug/CMakeFiles/iptest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/iptest.dir/depend
