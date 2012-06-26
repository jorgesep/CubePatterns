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
#target_link_libraries (TestCube Point)
#target_link_libraries (Patterns MathFunctions)
#target_link_libraries (CubePatterns CubePatterns)

add_library(PatternFactory SHARED PatternFactory)
add_library(Point SHARED Point.cpp)
#add_library(Cube Cube.cpp)
ADD_LIBRARY(CubePatterns SHARED Point Cube PatternFactory CubePatterns)

set_property(TARGET CubePatterns PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)


