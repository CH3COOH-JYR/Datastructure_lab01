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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build

# Include any dependencies generated for this target.
include CMakeFiles/TestSTL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TestSTL.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TestSTL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestSTL.dir/flags.make

CMakeFiles/TestSTL.dir/codegen:
.PHONY : CMakeFiles/TestSTL.dir/codegen

CMakeFiles/TestSTL.dir/test/test_list.cpp.o: CMakeFiles/TestSTL.dir/flags.make
CMakeFiles/TestSTL.dir/test/test_list.cpp.o: /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/test/test_list.cpp
CMakeFiles/TestSTL.dir/test/test_list.cpp.o: CMakeFiles/TestSTL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestSTL.dir/test/test_list.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestSTL.dir/test/test_list.cpp.o -MF CMakeFiles/TestSTL.dir/test/test_list.cpp.o.d -o CMakeFiles/TestSTL.dir/test/test_list.cpp.o -c /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/test/test_list.cpp

CMakeFiles/TestSTL.dir/test/test_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TestSTL.dir/test/test_list.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/test/test_list.cpp > CMakeFiles/TestSTL.dir/test/test_list.cpp.i

CMakeFiles/TestSTL.dir/test/test_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TestSTL.dir/test/test_list.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/test/test_list.cpp -o CMakeFiles/TestSTL.dir/test/test_list.cpp.s

CMakeFiles/TestSTL.dir/test/test_vector.cpp.o: CMakeFiles/TestSTL.dir/flags.make
CMakeFiles/TestSTL.dir/test/test_vector.cpp.o: /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/test/test_vector.cpp
CMakeFiles/TestSTL.dir/test/test_vector.cpp.o: CMakeFiles/TestSTL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TestSTL.dir/test/test_vector.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestSTL.dir/test/test_vector.cpp.o -MF CMakeFiles/TestSTL.dir/test/test_vector.cpp.o.d -o CMakeFiles/TestSTL.dir/test/test_vector.cpp.o -c /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/test/test_vector.cpp

CMakeFiles/TestSTL.dir/test/test_vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TestSTL.dir/test/test_vector.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/test/test_vector.cpp > CMakeFiles/TestSTL.dir/test/test_vector.cpp.i

CMakeFiles/TestSTL.dir/test/test_vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TestSTL.dir/test/test_vector.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/test/test_vector.cpp -o CMakeFiles/TestSTL.dir/test/test_vector.cpp.s

# Object files for target TestSTL
TestSTL_OBJECTS = \
"CMakeFiles/TestSTL.dir/test/test_list.cpp.o" \
"CMakeFiles/TestSTL.dir/test/test_vector.cpp.o"

# External object files for target TestSTL
TestSTL_EXTERNAL_OBJECTS =

TestSTL: CMakeFiles/TestSTL.dir/test/test_list.cpp.o
TestSTL: CMakeFiles/TestSTL.dir/test/test_vector.cpp.o
TestSTL: CMakeFiles/TestSTL.dir/build.make
TestSTL: Catch2/src/libCatch2Main.a
TestSTL: Catch2/src/libCatch2.a
TestSTL: CMakeFiles/TestSTL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable TestSTL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestSTL.dir/link.txt --verbose=$(VERBOSE)
	/opt/homebrew/bin/cmake -D TEST_TARGET=TestSTL -D TEST_EXECUTABLE=/Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build/TestSTL -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build -D TEST_SPEC= -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_LIST=TestSTL_TESTS -D TEST_REPORTER= -D TEST_OUTPUT_DIR= -D TEST_OUTPUT_PREFIX= -D TEST_OUTPUT_SUFFIX= -D TEST_DL_PATHS= -D CTEST_FILE=/Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build/TestSTL_tests-b12d07c.cmake -P /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/Catch2/extras/CatchAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/TestSTL.dir/build: TestSTL
.PHONY : CMakeFiles/TestSTL.dir/build

CMakeFiles/TestSTL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestSTL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestSTL.dir/clean

CMakeFiles/TestSTL.dir/depend:
	cd /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build /Users/renxuanyu/Desktop/Grade2/DataStructCode/lab/lab/build/CMakeFiles/TestSTL.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TestSTL.dir/depend

