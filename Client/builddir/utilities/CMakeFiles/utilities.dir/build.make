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
CMAKE_SOURCE_DIR = /home/sergiu/Desktop/CSD/Proiect/Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sergiu/Desktop/CSD/Proiect/Client/builddir

# Include any dependencies generated for this target.
include utilities/CMakeFiles/utilities.dir/depend.make

# Include the progress variables for this target.
include utilities/CMakeFiles/utilities.dir/progress.make

# Include the compile flags for this target's objects.
include utilities/CMakeFiles/utilities.dir/flags.make

utilities/CMakeFiles/utilities.dir/Utilities.cpp.o: utilities/CMakeFiles/utilities.dir/flags.make
utilities/CMakeFiles/utilities.dir/Utilities.cpp.o: ../utilities/Utilities.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sergiu/Desktop/CSD/Proiect/Client/builddir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utilities/CMakeFiles/utilities.dir/Utilities.cpp.o"
	cd /home/sergiu/Desktop/CSD/Proiect/Client/builddir/utilities && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utilities.dir/Utilities.cpp.o -c /home/sergiu/Desktop/CSD/Proiect/Client/utilities/Utilities.cpp

utilities/CMakeFiles/utilities.dir/Utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utilities.dir/Utilities.cpp.i"
	cd /home/sergiu/Desktop/CSD/Proiect/Client/builddir/utilities && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sergiu/Desktop/CSD/Proiect/Client/utilities/Utilities.cpp > CMakeFiles/utilities.dir/Utilities.cpp.i

utilities/CMakeFiles/utilities.dir/Utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utilities.dir/Utilities.cpp.s"
	cd /home/sergiu/Desktop/CSD/Proiect/Client/builddir/utilities && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sergiu/Desktop/CSD/Proiect/Client/utilities/Utilities.cpp -o CMakeFiles/utilities.dir/Utilities.cpp.s

# Object files for target utilities
utilities_OBJECTS = \
"CMakeFiles/utilities.dir/Utilities.cpp.o"

# External object files for target utilities
utilities_EXTERNAL_OBJECTS =

utilities/libutilities.a: utilities/CMakeFiles/utilities.dir/Utilities.cpp.o
utilities/libutilities.a: utilities/CMakeFiles/utilities.dir/build.make
utilities/libutilities.a: utilities/CMakeFiles/utilities.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sergiu/Desktop/CSD/Proiect/Client/builddir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libutilities.a"
	cd /home/sergiu/Desktop/CSD/Proiect/Client/builddir/utilities && $(CMAKE_COMMAND) -P CMakeFiles/utilities.dir/cmake_clean_target.cmake
	cd /home/sergiu/Desktop/CSD/Proiect/Client/builddir/utilities && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utilities.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utilities/CMakeFiles/utilities.dir/build: utilities/libutilities.a

.PHONY : utilities/CMakeFiles/utilities.dir/build

utilities/CMakeFiles/utilities.dir/clean:
	cd /home/sergiu/Desktop/CSD/Proiect/Client/builddir/utilities && $(CMAKE_COMMAND) -P CMakeFiles/utilities.dir/cmake_clean.cmake
.PHONY : utilities/CMakeFiles/utilities.dir/clean

utilities/CMakeFiles/utilities.dir/depend:
	cd /home/sergiu/Desktop/CSD/Proiect/Client/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sergiu/Desktop/CSD/Proiect/Client /home/sergiu/Desktop/CSD/Proiect/Client/utilities /home/sergiu/Desktop/CSD/Proiect/Client/builddir /home/sergiu/Desktop/CSD/Proiect/Client/builddir/utilities /home/sergiu/Desktop/CSD/Proiect/Client/builddir/utilities/CMakeFiles/utilities.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utilities/CMakeFiles/utilities.dir/depend
