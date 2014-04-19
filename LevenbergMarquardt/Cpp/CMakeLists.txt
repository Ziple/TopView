cmake_minimum_required( VERSION 2.6 )

# --------------------------------------------
# Project name definition
# --------------------------------------------
project( "Levenberg-Marquardt" )

cmake_policy( SET CMP0015 NEW )

# --------------------------------------------
# Allow the developer to select if Dynamic or Static libraries are built
# --------------------------------------------
option( BUILD_SHARED_LIBS "Build as Shared Libraries" OFF )

if( BUILD_SHARED_LIBS )
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  set( lm_lib_type SHARED )
  add_definitions( -DLM_BUILDING_LIBRARY  -DLM_DYNAMIC )
else()
  set( lm_lib_type STATIC )
endif( BUILD_SHARED_LIBS )
# --------------------------------------------

# --------------------------------------------
# Add -d to debug builds
# --------------------------------------------
set( CMAKE_DEBUG_POSTFIX -d )

# --------------------------------------------
# Add -s to the static libs
# --------------------------------------------
if( NOT BUILD_SHARED_LIBS )
	set( lm_lib_suffix -s )
else()
	set( lm_lib_suffix  )
endif( NOT BUILD_SHARED_LIBS )

# --------------------------------------------
# Correctly named.
# --------------------------------------------

# --------------------------------------------
# Add the compiler include / lib paths
# to the default CMake paths
# --------------------------------------------
set(CMAKE_INCLUDE_PATH $CMAKE_INCLUDE_PATH $ENV{INCLUDE})
set(CMAKE_LIBRARY_PATH $CMAKE_LIBRARY_PATH $ENV{LIB})
set(CMAKE_LIBRARY_PATH $CMAKE_LIBRARY_PATH $LIBRARY_OUTPUT_PATH)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# --------------------------------------------
# Add the folder to the compilation includes path
# --------------------------------------------
include_directories( include )

find_package(EIGEN3  REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# --------------------------------------------
# Add the module to the build
# --------------------------------------------
file(
	GLOB
	core_source_files
	src/*.cpp
)

file(
	GLOB
	core_header_files
	include/*.hpp
	include/*.h
	src/*.hpp
)

set( lmLibName lm${lm_lib_suffix})

add_library(
	${lmLibName}
	${lm_lib_type}
	${core_source_files}
	${core_header_files}
)