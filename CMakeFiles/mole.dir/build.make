# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\narug\Desktop\sdl2-mixer-sample-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\narug\Desktop\build-sdl2-mixer-sample-master-MinGW-Debug

# Include any dependencies generated for this target.
include CMakeFiles/mole.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mole.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mole.dir/flags.make

CMakeFiles/mole.dir/src/main.c.obj: CMakeFiles/mole.dir/flags.make
CMakeFiles/mole.dir/src/main.c.obj: CMakeFiles/mole.dir/includes_C.rsp
CMakeFiles/mole.dir/src/main.c.obj: C:/Users/narug/Desktop/sdl2-mixer-sample-master/src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\narug\Desktop\build-sdl2-mixer-sample-master-MinGW-Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mole.dir/src/main.c.obj"
	C:\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\mole.dir\src\main.c.obj   -c C:\Users\narug\Desktop\sdl2-mixer-sample-master\src\main.c

CMakeFiles/mole.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mole.dir/src/main.c.i"
	C:\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\narug\Desktop\sdl2-mixer-sample-master\src\main.c > CMakeFiles\mole.dir\src\main.c.i

CMakeFiles/mole.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mole.dir/src/main.c.s"
	C:\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\narug\Desktop\sdl2-mixer-sample-master\src\main.c -o CMakeFiles\mole.dir\src\main.c.s

# Object files for target mole
mole_OBJECTS = \
"CMakeFiles/mole.dir/src/main.c.obj"

# External object files for target mole
mole_EXTERNAL_OBJECTS =

mole.exe: CMakeFiles/mole.dir/src/main.c.obj
mole.exe: CMakeFiles/mole.dir/build.make
mole.exe: C:/SDL2_image-2.0.5/i686-w64-mingw32/lib/libSDL2_image.dll.a
mole.exe: C:/SDL2_ttf-2.0.15/i686-w64-mingw32/lib/libSDL2_ttf.dll.a
mole.exe: C:/SDL2_mixer-2.0.4/i686-w64-mingw32/lib/libSDL2_mixer.dll.a
mole.exe: C:/SDL2_gfx-1.0.4/lib/libSDL2_gfx.dll.a
mole.exe: C:/SDL2-2.0.10/i686-w64-mingw32/lib/libSDL2main.a
mole.exe: C:/SDL2-2.0.10/i686-w64-mingw32/lib/libSDL2.dll.a
mole.exe: CMakeFiles/mole.dir/linklibs.rsp
mole.exe: CMakeFiles/mole.dir/objects1.rsp
mole.exe: CMakeFiles/mole.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\narug\Desktop\build-sdl2-mixer-sample-master-MinGW-Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable mole.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mole.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mole.dir/build: mole.exe

.PHONY : CMakeFiles/mole.dir/build

CMakeFiles/mole.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mole.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mole.dir/clean

CMakeFiles/mole.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\narug\Desktop\sdl2-mixer-sample-master C:\Users\narug\Desktop\sdl2-mixer-sample-master C:\Users\narug\Desktop\build-sdl2-mixer-sample-master-MinGW-Debug C:\Users\narug\Desktop\build-sdl2-mixer-sample-master-MinGW-Debug C:\Users\narug\Desktop\build-sdl2-mixer-sample-master-MinGW-Debug\CMakeFiles\mole.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mole.dir/depend

