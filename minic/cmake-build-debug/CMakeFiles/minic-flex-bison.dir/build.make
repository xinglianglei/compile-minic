# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\CompilerTools\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = D:\CompilerTools\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CompilerTools\code\minic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CompilerTools\code\minic\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/minic-flex-bison.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/minic-flex-bison.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/minic-flex-bison.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minic-flex-bison.dir/flags.make

D:/CompilerTools/code/minic/minic_lex.cpp: D:/CompilerTools/code/minic/minic.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating D:/CompilerTools/code/minic/minic_lex.cpp, D:/CompilerTools/code/minic/minic_lex.h"
	D:\CompilerTools\msys64\usr\bin\flex.exe -o D:/CompilerTools/code/minic/minic_lex.cpp --header-file=D:/CompilerTools/code/minic/minic_lex.h D:/CompilerTools/code/minic/minic.l

D:/CompilerTools/code/minic/minic_lex.h: D:/CompilerTools/code/minic/minic_lex.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate D:\CompilerTools\code\minic\minic_lex.h

D:/CompilerTools/code/minic/minic_yacc.cpp: D:/CompilerTools/code/minic/minic.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating D:/CompilerTools/code/minic/minic_yacc.cpp, D:/CompilerTools/code/minic/minic_yacc.h"
	D:\CompilerTools\msys64\usr\bin\bison.exe -d -o D:/CompilerTools/code/minic/minic_yacc.cpp --header=D:/CompilerTools/code/minic/minic_yacc.h D:/CompilerTools/code/minic/minic.y

D:/CompilerTools/code/minic/minic_yacc.h: D:/CompilerTools/code/minic/minic_yacc.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate D:\CompilerTools\code\minic\minic_yacc.h

CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.obj: CMakeFiles/minic-flex-bison.dir/flags.make
CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.obj: CMakeFiles/minic-flex-bison.dir/includes_CXX.rsp
CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.obj: D:/CompilerTools/code/minic/minic_lex.cpp
CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.obj: CMakeFiles/minic-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.obj"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.obj -MF CMakeFiles\minic-flex-bison.dir\minic_lex.cpp.obj.d -o CMakeFiles\minic-flex-bison.dir\minic_lex.cpp.obj -c D:\CompilerTools\code\minic\minic_lex.cpp

CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.i"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CompilerTools\code\minic\minic_lex.cpp > CMakeFiles\minic-flex-bison.dir\minic_lex.cpp.i

CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.s"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CompilerTools\code\minic\minic_lex.cpp -o CMakeFiles\minic-flex-bison.dir\minic_lex.cpp.s

CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.obj: CMakeFiles/minic-flex-bison.dir/flags.make
CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.obj: CMakeFiles/minic-flex-bison.dir/includes_CXX.rsp
CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.obj: D:/CompilerTools/code/minic/minic_yacc.cpp
CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.obj: CMakeFiles/minic-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.obj"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.obj -MF CMakeFiles\minic-flex-bison.dir\minic_yacc.cpp.obj.d -o CMakeFiles\minic-flex-bison.dir\minic_yacc.cpp.obj -c D:\CompilerTools\code\minic\minic_yacc.cpp

CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.i"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CompilerTools\code\minic\minic_yacc.cpp > CMakeFiles\minic-flex-bison.dir\minic_yacc.cpp.i

CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.s"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CompilerTools\code\minic\minic_yacc.cpp -o CMakeFiles\minic-flex-bison.dir\minic_yacc.cpp.s

CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.obj: CMakeFiles/minic-flex-bison.dir/flags.make
CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.obj: CMakeFiles/minic-flex-bison.dir/includes_CXX.rsp
CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.obj: D:/CompilerTools/code/minic/ast_minic.cpp
CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.obj: CMakeFiles/minic-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.obj"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.obj -MF CMakeFiles\minic-flex-bison.dir\ast_minic.cpp.obj.d -o CMakeFiles\minic-flex-bison.dir\ast_minic.cpp.obj -c D:\CompilerTools\code\minic\ast_minic.cpp

CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.i"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CompilerTools\code\minic\ast_minic.cpp > CMakeFiles\minic-flex-bison.dir\ast_minic.cpp.i

CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.s"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CompilerTools\code\minic\ast_minic.cpp -o CMakeFiles\minic-flex-bison.dir\ast_minic.cpp.s

CMakeFiles/minic-flex-bison.dir/main.cpp.obj: CMakeFiles/minic-flex-bison.dir/flags.make
CMakeFiles/minic-flex-bison.dir/main.cpp.obj: CMakeFiles/minic-flex-bison.dir/includes_CXX.rsp
CMakeFiles/minic-flex-bison.dir/main.cpp.obj: D:/CompilerTools/code/minic/main.cpp
CMakeFiles/minic-flex-bison.dir/main.cpp.obj: CMakeFiles/minic-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/minic-flex-bison.dir/main.cpp.obj"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minic-flex-bison.dir/main.cpp.obj -MF CMakeFiles\minic-flex-bison.dir\main.cpp.obj.d -o CMakeFiles\minic-flex-bison.dir\main.cpp.obj -c D:\CompilerTools\code\minic\main.cpp

CMakeFiles/minic-flex-bison.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minic-flex-bison.dir/main.cpp.i"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CompilerTools\code\minic\main.cpp > CMakeFiles\minic-flex-bison.dir\main.cpp.i

CMakeFiles/minic-flex-bison.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minic-flex-bison.dir/main.cpp.s"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CompilerTools\code\minic\main.cpp -o CMakeFiles\minic-flex-bison.dir\main.cpp.s

CMakeFiles/minic-flex-bison.dir/symbol.cpp.obj: CMakeFiles/minic-flex-bison.dir/flags.make
CMakeFiles/minic-flex-bison.dir/symbol.cpp.obj: CMakeFiles/minic-flex-bison.dir/includes_CXX.rsp
CMakeFiles/minic-flex-bison.dir/symbol.cpp.obj: D:/CompilerTools/code/minic/symbol.cpp
CMakeFiles/minic-flex-bison.dir/symbol.cpp.obj: CMakeFiles/minic-flex-bison.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/minic-flex-bison.dir/symbol.cpp.obj"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minic-flex-bison.dir/symbol.cpp.obj -MF CMakeFiles\minic-flex-bison.dir\symbol.cpp.obj.d -o CMakeFiles\minic-flex-bison.dir\symbol.cpp.obj -c D:\CompilerTools\code\minic\symbol.cpp

CMakeFiles/minic-flex-bison.dir/symbol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minic-flex-bison.dir/symbol.cpp.i"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CompilerTools\code\minic\symbol.cpp > CMakeFiles\minic-flex-bison.dir\symbol.cpp.i

CMakeFiles/minic-flex-bison.dir/symbol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minic-flex-bison.dir/symbol.cpp.s"
	D:\CompilerTools\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CompilerTools\code\minic\symbol.cpp -o CMakeFiles\minic-flex-bison.dir\symbol.cpp.s

# Object files for target minic-flex-bison
minic__flex__bison_OBJECTS = \
"CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.obj" \
"CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.obj" \
"CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.obj" \
"CMakeFiles/minic-flex-bison.dir/main.cpp.obj" \
"CMakeFiles/minic-flex-bison.dir/symbol.cpp.obj"

# External object files for target minic-flex-bison
minic__flex__bison_EXTERNAL_OBJECTS =

minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/minic_lex.cpp.obj
minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/minic_yacc.cpp.obj
minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/ast_minic.cpp.obj
minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/main.cpp.obj
minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/symbol.cpp.obj
minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/build.make
minic-flex-bison.exe: D:/CompilerTools/msys64/mingw64/lib/libcdt.dll.a
minic-flex-bison.exe: D:/CompilerTools/msys64/mingw64/lib/libgvc.dll.a
minic-flex-bison.exe: D:/CompilerTools/msys64/mingw64/lib/libcgraph.dll.a
minic-flex-bison.exe: D:/CompilerTools/msys64/mingw64/lib/libpathplan.dll.a
minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/linkLibs.rsp
minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/objects1.rsp
minic-flex-bison.exe: CMakeFiles/minic-flex-bison.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable minic-flex-bison.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\minic-flex-bison.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minic-flex-bison.dir/build: minic-flex-bison.exe
.PHONY : CMakeFiles/minic-flex-bison.dir/build

CMakeFiles/minic-flex-bison.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\minic-flex-bison.dir\cmake_clean.cmake
.PHONY : CMakeFiles/minic-flex-bison.dir/clean

CMakeFiles/minic-flex-bison.dir/depend: D:/CompilerTools/code/minic/minic_lex.cpp
CMakeFiles/minic-flex-bison.dir/depend: D:/CompilerTools/code/minic/minic_lex.h
CMakeFiles/minic-flex-bison.dir/depend: D:/CompilerTools/code/minic/minic_yacc.cpp
CMakeFiles/minic-flex-bison.dir/depend: D:/CompilerTools/code/minic/minic_yacc.h
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CompilerTools\code\minic D:\CompilerTools\code\minic D:\CompilerTools\code\minic\cmake-build-debug D:\CompilerTools\code\minic\cmake-build-debug D:\CompilerTools\code\minic\cmake-build-debug\CMakeFiles\minic-flex-bison.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minic-flex-bison.dir/depend
