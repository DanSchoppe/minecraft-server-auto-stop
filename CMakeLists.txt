cmake_minimum_required (VERSION 3.0.2)
project(minecraft-server-stop)

# Version number
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

# Pass CMake settings to source through a header file
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# Add bin to search path for include files
include_directories("${PROJECT_BINARY_DIR}")

# Executable
add_executable(minecraft-server-stop main.cpp)
