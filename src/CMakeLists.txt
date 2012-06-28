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

#delete generated files  
SET_DIRECTORY_PROPERTIES (
   PROPERTIES 
     ADDITIONAL_MAKE_CLEAN_FILES "MeteoDevice.h"
     ADDITIONAL_MAKE_CLEAN_FILES "MeteoDevice.cpp"
     ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_SOURCE_DIR}/*~"
     ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_SOURCE_DIR}/../*~"
)
# Set DEBUG option
option(DEBUG "DEBUG option to print out more info" ON)

# for ../bin/TestCube executable
ADD_EXECUTABLE (TestCube TestCube)
TARGET_LINK_LIBRARIES (TestCube CubePatterns)
set_property(TARGET TestCube PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

ADD_EXECUTABLE (TestPattern TestPattern)
TARGET_LINK_LIBRARIES (TestPattern CubePatterns)
set_property(TARGET TestPattern PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)


#delete bin files in make clean
SET_DIRECTORY_PROPERTIES (
   PROPERTIES
      ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_SOURCE_DIR}/../bin/*"
)

#ADD_LIBRARY(PatternFactory SHARED PatternFactory)
#ADD_LIBRARY(Cube SHARED Cube.cpp)
#ADD_LIBRARY(Point SHARED Point.cpp)
#ADD_LIBRARY(CubePatterns SHARED CubePatterns.cpp)

ADD_LIBRARY(CubePatterns SHARED Point Cube PatternFactory CubePatterns)

set_property(TARGET CubePatterns PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)


