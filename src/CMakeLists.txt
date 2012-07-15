cmake_minimum_required (VERSION 2.6)
project (TransitionTemplate)

# The version number.
set (Patterns_VERSION_MAJOR 1)
set (Patterns_VERSION_MINOR 0)

# add the binary tree to the search path for include files
# so that we will find PatternsConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/../include")
include_directories("${PROJECT_BINARY_DIR}/../mesher")

#delete generated files  
SET_DIRECTORY_PROPERTIES (
   PROPERTIES 
     ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_SOURCE_DIR}/*~"
     ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_SOURCE_DIR}/../*~"
)
# Set DEBUG option
option(DEBUG "DEBUG option to print out more info" ON)

# for ../bin/TestCube executable
ADD_EXECUTABLE (TestCube TestCube)
TARGET_LINK_LIBRARIES (TestCube TransitionTemplate)
set_property(TARGET TestCube PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

ADD_EXECUTABLE (TestPattern TestPattern)
TARGET_LINK_LIBRARIES (TestPattern TransitionTemplate)
set_property(TARGET TestPattern PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)


#delete bin files in make clean
SET_DIRECTORY_PROPERTIES (
   PROPERTIES
      ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_SOURCE_DIR}/../bin/*"
)

ADD_LIBRARY(TransitionTemplate SHARED Point Cube PatternFactory TransitionTemplate ../mesher/MeshPoint ../mesher/Point3D)

set_property(TARGET TransitionTemplate PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)


