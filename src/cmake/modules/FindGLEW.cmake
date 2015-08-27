# Find GLEW library and include paths for CSD462
# This defines the following:
#
# GLEW_FOUND             If GLEW is found
# GLEW_LIBRARIES         GLEW libraries
# GLEW_INCLUDE_DIRS      GLEW include directories
# GLEW_LIBRARY_DIRS      GLEW library directories

# GLEW static library
find_library(GLEW_LIBRARIES
    NAMES libglew.a
    PATHS ${PROJECT_SOURCE_DIR}/glew
    DOC "GLEW library")

# GLEW library dir
find_path(GLEW_LIBRARY_DIRS
    NAMES libglew.a
    PATHS ${PROJECT_SOURCE_DIR}/glew
    DOC "462 include directories")

# GLEW include dir
find_path(GLEW_INCLUDE_DIRS
    NAMES glew.h
    PATHS ${PROJECT_SOURCE_DIR}/glew/GLEW
    DOC "462 include directories")

# Version
set(GLEW_VERSION 1.0)

# Set package standard args
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW 
    REQUIRED_VARS GLEW_INCLUDE_DIRS GLEW_LIBRARY_DIRS GLEW_LIBRARIES
    VERSION_VAR GLEW_VERSION)
