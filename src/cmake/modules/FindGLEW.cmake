# Find GLEW library and include paths for CSD462
# This defines the following:
#
# GLEW_FOUND             If GLEW is found
# GLEW_LIBRARIES         GLEW libraries
# GLEW_INCLUDE_DIRS      GLEW include directories
# GLEW_LIBRARY_DIRS      GLEW library directories

if(UNIX)
  set(GLEW_INC_NAMES GLEW/glew.h)
  set(GLEW_LIB_NAMES libglew.a)
  if(APPLE)
    set(GLEW_LIB_NAMES libglew_osx.a)
  endif(APPLE)
endif(UNIX)

# GLEW static library
find_library(GLEW_LIBRARIES
    NAMES ${GLEW_LIB_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/glew/lib
    DOC "GLEW library")

# GLEW library dir
find_path(GLEW_LIBRARY_DIRS
    NAMES ${GLEW_LIB_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/glew/lib
    DOC "GLEW include directories")

# GLEW include dir
find_path(GLEW_INCLUDE_DIRS
    NAMES ${GLEW_INC_NAMES}
    PATHS ${PROJECT_SOURCE_DIR}/glew/include/
    DOC "GLEW include directories")

# Version
set(GLEW_VERSION 1.0)

# Set package standard args
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW 
    REQUIRED_VARS GLEW_INCLUDE_DIRS GLEW_LIBRARY_DIRS GLEW_LIBRARIES
    VERSION_VAR GLEW_VERSION)
