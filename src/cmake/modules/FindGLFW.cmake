# Find GLFW library and include paths for CSD462
# This defines the following:
#
# GLFW_FOUND             If GLFW is found
# GLFW_LIBRARIES         GLFW libraries
# GLFW_INCLUDE_DIRS      GLFW include directories
# GLFW_LIBRARY_DIRS      GLFW library directories

if(UNIX)
  set(GLFW_INC_NAMES glfw.h)
  set(GLFW_LIB_NAMES libglfw.a)
  if(APPLE)
    set(GLFW_LIB_NAMES libglfw_osx.a)
  endif(APPLE)
endif(UNIX)

# GLFW static library
find_library(GLFW_LIBRARIES
    NAMES ${GLFW_LIB_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/glfw/lib
    DOC "GLFW library")

# GLFW library dir
find_path(GLFW_LIBRARY_DIRS
    NAMES ${GLFW_LIB_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/glfw/lib
    DOC "GLFW include directories")

# GLFW include dir
find_path(GLFW_INCLUDE_DIRS
    NAMES ${GLFW_INC_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/glfw/include/GLFW
    DOC "GLFW include directories")

# Version
set(GLFW_VERSION 1.0)

# Set package standard args
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW 
    REQUIRED_VARS GLFW_INCLUDE_DIRS GLFW_LIBRARY_DIRS GLFW_LIBRARIES
    VERSION_VAR GLFW_VERSION)
