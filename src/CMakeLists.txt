cmake_minimum_required (VERSION 2.6)
project (CubePatterns)

# The version number.
set (Patterns_VERSION_MAJOR 1)
set (Patterns_VERSION_MINOR 0)

#file(MAKE_DIRECTORY ../lib ../bin ../test)

# configure a header file to pass some of the CMake sttings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/PatternsConfig.h.in"
  "${PROJECT_SOURCE_DIR}/../include/PatternsConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find PatternsConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/../include")

# for ../bin/TestCube executable
ADD_EXECUTABLE (TestCube TestCube)
TARGET_LINK_LIBRARIES (TestCube CubePatterns)
set_property(TARGET TestCube PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)


#delete bin files in make clean
SET_DIRECTORY_PROPERTIES (
   PROPERTIES
      ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_SOURCE_DIR}/../bin/*"
)
#target_link_libraries (TestCube Point)
#target_link_libraries (Patterns MathFunctions)
#target_link_libraries (CubePatterns CubePatterns)

add_library(Patterns SHARED Patterns)
#add_library(Point Point.cpp)
#add_library(Cube Cube.cpp)
ADD_LIBRARY(CubePatterns SHARED Point Cube)

set_property(TARGET CubePatterns PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)


