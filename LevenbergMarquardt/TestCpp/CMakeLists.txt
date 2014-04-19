cmake_minimum_required( VERSION 2.6 )

# --------------------------------------------
# Project name definition
# --------------------------------------------
project( "Test Levenberg-Marquardt" )

cmake_policy( SET CMP0015 NEW )

# --------------------------------------------
# Add the compiler include / lib paths
# to the default CMake paths
# --------------------------------------------
set(CMAKE_INCLUDE_PATH $CMAKE_INCLUDE_PATH $ENV{INCLUDE})
set(CMAKE_LIBRARY_PATH $CMAKE_LIBRARY_PATH $ENV{LIB})

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# --------------------------------------------
# Add the folder to the compilation includes path
# --------------------------------------------
include_directories( include )

file(
    GLOB_RECURSE
    source_files
    src/*.cpp
)

file(
    GLOB_RECURSE
    header_files
    include/*.hpp
)

add_executable(
    TestLM
    ${source_files}
    ${header_files}
)

# --------------------------------------------
# Add -d to debug lib names
# --------------------------------------------
set( lm_lib_debug_suffix "-d" )

# --------------------------------------------
# Add -s to lib names
# --------------------------------------------
if( NOT USE_SHARED_LIBS )
    set( lm_lib_suffix -s )
endif( NOT USE_SHARED_LIBS )

set( lmLibName lm${lm_lib_suffix} )

target_link_libraries( TestLM optimized ${lmLibName} )
target_link_libraries( TestLM debug ${lmLibName}${lm_lib_debug_suffix} )

