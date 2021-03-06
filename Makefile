# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/davide/projekty/studies/warcaby/Symulator-wieloagentowy/Symulator-wieloagentowy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/davide/projekty/studies/warcaby/Symulator-wieloagentowy/Symulator-wieloagentowy

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/davide/projekty/studies/warcaby/Symulator-wieloagentowy/Symulator-wieloagentowy/CMakeFiles /home/davide/projekty/studies/warcaby/Symulator-wieloagentowy/Symulator-wieloagentowy/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/davide/projekty/studies/warcaby/Symulator-wieloagentowy/Symulator-wieloagentowy/CMakeFiles 0
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
# Target rules for targets named debug

# Build rule for target.
debug: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 debug
.PHONY : debug

# fast build rule for target.
debug/fast:
	$(MAKE) -f CMakeFiles/debug.dir/build.make CMakeFiles/debug.dir/build
.PHONY : debug/fast

#=============================================================================
# Target rules for targets named app

# Build rule for target.
app: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 app
.PHONY : app

# fast build rule for target.
app/fast:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/build
.PHONY : app/fast

#=============================================================================
# Target rules for targets named release

# Build rule for target.
release: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 release
.PHONY : release

# fast build rule for target.
release/fast:
	$(MAKE) -f CMakeFiles/release.dir/build.make CMakeFiles/release.dir/build
.PHONY : release/fast

sources/agent.o: sources/agent.cpp.o

.PHONY : sources/agent.o

# target to build an object file
sources/agent.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/agent.cpp.o
.PHONY : sources/agent.cpp.o

sources/agent.i: sources/agent.cpp.i

.PHONY : sources/agent.i

# target to preprocess a source file
sources/agent.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/agent.cpp.i
.PHONY : sources/agent.cpp.i

sources/agent.s: sources/agent.cpp.s

.PHONY : sources/agent.s

# target to generate assembly for a file
sources/agent.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/agent.cpp.s
.PHONY : sources/agent.cpp.s

sources/console.o: sources/console.cpp.o

.PHONY : sources/console.o

# target to build an object file
sources/console.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/console.cpp.o
.PHONY : sources/console.cpp.o

sources/console.i: sources/console.cpp.i

.PHONY : sources/console.i

# target to preprocess a source file
sources/console.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/console.cpp.i
.PHONY : sources/console.cpp.i

sources/console.s: sources/console.cpp.s

.PHONY : sources/console.s

# target to generate assembly for a file
sources/console.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/console.cpp.s
.PHONY : sources/console.cpp.s

sources/elements.o: sources/elements.cpp.o

.PHONY : sources/elements.o

# target to build an object file
sources/elements.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/elements.cpp.o
.PHONY : sources/elements.cpp.o

sources/elements.i: sources/elements.cpp.i

.PHONY : sources/elements.i

# target to preprocess a source file
sources/elements.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/elements.cpp.i
.PHONY : sources/elements.cpp.i

sources/elements.s: sources/elements.cpp.s

.PHONY : sources/elements.s

# target to generate assembly for a file
sources/elements.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/elements.cpp.s
.PHONY : sources/elements.cpp.s

sources/graph.o: sources/graph.cpp.o

.PHONY : sources/graph.o

# target to build an object file
sources/graph.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/graph.cpp.o
.PHONY : sources/graph.cpp.o

sources/graph.i: sources/graph.cpp.i

.PHONY : sources/graph.i

# target to preprocess a source file
sources/graph.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/graph.cpp.i
.PHONY : sources/graph.cpp.i

sources/graph.s: sources/graph.cpp.s

.PHONY : sources/graph.s

# target to generate assembly for a file
sources/graph.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/graph.cpp.s
.PHONY : sources/graph.cpp.s

sources/main.o: sources/main.cpp.o

.PHONY : sources/main.o

# target to build an object file
sources/main.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/main.cpp.o
.PHONY : sources/main.cpp.o

sources/main.i: sources/main.cpp.i

.PHONY : sources/main.i

# target to preprocess a source file
sources/main.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/main.cpp.i
.PHONY : sources/main.cpp.i

sources/main.s: sources/main.cpp.s

.PHONY : sources/main.s

# target to generate assembly for a file
sources/main.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/main.cpp.s
.PHONY : sources/main.cpp.s

sources/simulation.o: sources/simulation.cpp.o

.PHONY : sources/simulation.o

# target to build an object file
sources/simulation.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/simulation.cpp.o
.PHONY : sources/simulation.cpp.o

sources/simulation.i: sources/simulation.cpp.i

.PHONY : sources/simulation.i

# target to preprocess a source file
sources/simulation.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/simulation.cpp.i
.PHONY : sources/simulation.cpp.i

sources/simulation.s: sources/simulation.cpp.s

.PHONY : sources/simulation.s

# target to generate assembly for a file
sources/simulation.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/sources/simulation.cpp.s
.PHONY : sources/simulation.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... debug"
	@echo "... edit_cache"
	@echo "... app"
	@echo "... release"
	@echo "... sources/agent.o"
	@echo "... sources/agent.i"
	@echo "... sources/agent.s"
	@echo "... sources/console.o"
	@echo "... sources/console.i"
	@echo "... sources/console.s"
	@echo "... sources/elements.o"
	@echo "... sources/elements.i"
	@echo "... sources/elements.s"
	@echo "... sources/graph.o"
	@echo "... sources/graph.i"
	@echo "... sources/graph.s"
	@echo "... sources/main.o"
	@echo "... sources/main.i"
	@echo "... sources/main.s"
	@echo "... sources/simulation.o"
	@echo "... sources/simulation.i"
	@echo "... sources/simulation.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

