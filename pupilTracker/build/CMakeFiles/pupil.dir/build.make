# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/manasi/Documents/opencvstuff/Day10

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/manasi/Documents/opencvstuff/Day10/build

# Include any dependencies generated for this target.
include CMakeFiles/pupil.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pupil.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pupil.dir/flags.make

CMakeFiles/pupil.dir/pupil.cpp.o: CMakeFiles/pupil.dir/flags.make
CMakeFiles/pupil.dir/pupil.cpp.o: ../pupil.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/manasi/Documents/opencvstuff/Day10/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/pupil.dir/pupil.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pupil.dir/pupil.cpp.o -c /home/manasi/Documents/opencvstuff/Day10/pupil.cpp

CMakeFiles/pupil.dir/pupil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pupil.dir/pupil.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/manasi/Documents/opencvstuff/Day10/pupil.cpp > CMakeFiles/pupil.dir/pupil.cpp.i

CMakeFiles/pupil.dir/pupil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pupil.dir/pupil.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/manasi/Documents/opencvstuff/Day10/pupil.cpp -o CMakeFiles/pupil.dir/pupil.cpp.s

CMakeFiles/pupil.dir/pupil.cpp.o.requires:
.PHONY : CMakeFiles/pupil.dir/pupil.cpp.o.requires

CMakeFiles/pupil.dir/pupil.cpp.o.provides: CMakeFiles/pupil.dir/pupil.cpp.o.requires
	$(MAKE) -f CMakeFiles/pupil.dir/build.make CMakeFiles/pupil.dir/pupil.cpp.o.provides.build
.PHONY : CMakeFiles/pupil.dir/pupil.cpp.o.provides

CMakeFiles/pupil.dir/pupil.cpp.o.provides.build: CMakeFiles/pupil.dir/pupil.cpp.o

# Object files for target pupil
pupil_OBJECTS = \
"CMakeFiles/pupil.dir/pupil.cpp.o"

# External object files for target pupil
pupil_EXTERNAL_OBJECTS =

pupil: CMakeFiles/pupil.dir/pupil.cpp.o
pupil: CMakeFiles/pupil.dir/build.make
pupil: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
pupil: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
pupil: CMakeFiles/pupil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable pupil"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pupil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pupil.dir/build: pupil
.PHONY : CMakeFiles/pupil.dir/build

CMakeFiles/pupil.dir/requires: CMakeFiles/pupil.dir/pupil.cpp.o.requires
.PHONY : CMakeFiles/pupil.dir/requires

CMakeFiles/pupil.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pupil.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pupil.dir/clean

CMakeFiles/pupil.dir/depend:
	cd /home/manasi/Documents/opencvstuff/Day10/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/manasi/Documents/opencvstuff/Day10 /home/manasi/Documents/opencvstuff/Day10 /home/manasi/Documents/opencvstuff/Day10/build /home/manasi/Documents/opencvstuff/Day10/build /home/manasi/Documents/opencvstuff/Day10/build/CMakeFiles/pupil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pupil.dir/depend
