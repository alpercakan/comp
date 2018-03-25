# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alpercakan/Desktop/comp_compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alpercakan/Desktop/comp_compiler

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.10.0/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/local/Cellar/cmake/3.10.0/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/alpercakan/Desktop/comp_compiler/CMakeFiles /Users/alpercakan/Desktop/comp_compiler/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/alpercakan/Desktop/comp_compiler/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named comp_compiler

# Build rule for target.
comp_compiler: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 comp_compiler
.PHONY : comp_compiler

# fast build rule for target.
comp_compiler/fast:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/build
.PHONY : comp_compiler/fast

AsmGenerator.o: AsmGenerator.cpp.o

.PHONY : AsmGenerator.o

# target to build an object file
AsmGenerator.cpp.o:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/AsmGenerator.cpp.o
.PHONY : AsmGenerator.cpp.o

AsmGenerator.i: AsmGenerator.cpp.i

.PHONY : AsmGenerator.i

# target to preprocess a source file
AsmGenerator.cpp.i:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/AsmGenerator.cpp.i
.PHONY : AsmGenerator.cpp.i

AsmGenerator.s: AsmGenerator.cpp.s

.PHONY : AsmGenerator.s

# target to generate assembly for a file
AsmGenerator.cpp.s:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/AsmGenerator.cpp.s
.PHONY : AsmGenerator.cpp.s

Parser.o: Parser.cpp.o

.PHONY : Parser.o

# target to build an object file
Parser.cpp.o:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/Parser.cpp.o
.PHONY : Parser.cpp.o

Parser.i: Parser.cpp.i

.PHONY : Parser.i

# target to preprocess a source file
Parser.cpp.i:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/Parser.cpp.i
.PHONY : Parser.cpp.i

Parser.s: Parser.cpp.s

.PHONY : Parser.s

# target to generate assembly for a file
Parser.cpp.s:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/Parser.cpp.s
.PHONY : Parser.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/comp_compiler.dir/build.make CMakeFiles/comp_compiler.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... comp_compiler"
	@echo "... AsmGenerator.o"
	@echo "... AsmGenerator.i"
	@echo "... AsmGenerator.s"
	@echo "... Parser.o"
	@echo "... Parser.i"
	@echo "... Parser.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

