# Find GLFW library and include paths for CSD462
# This defines the following:
#
# GLFW_FOUND             If GLFW is found
# GLFW_LIBRARIES         GLFW libraries
# GLFW_INCLUDE_DIRS      GLFW include directories
# GLFW_LIBRARY_DIRS      GLFW library directories

# GLFW static library
find_library(GLFW_LIBRARIES
    NAMES libglfw.a
    PATHS ${PROJECT_SOURCE_DIR}/glfw
    DOC "GLFW library")

# GLFW library dir
find_path(GLFW_LIBRARY_DIRS
    NAMES libglfw.a
    PATHS ${PROJECT_SOURCE_DIR}/glfw
    DOC "462 include directories")

# GLFW include dir
find_path(GLFW_INCLUDE_DIRS
    NAMES glfw.h
    PATHS ${PROJECT_SOURCE_DIR}/glfw/GLFW
    DOC "462 include directories")

# Version
set(GLFW_VERSION 1.0)

# Set package standard args
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW 
    REQUIRED_VARS GLFW_INCLUDE_DIRS GLFW_LIBRARY_DIRS GLFW_LIBRARIES
    VERSION_VAR GLFW_VERSION)
