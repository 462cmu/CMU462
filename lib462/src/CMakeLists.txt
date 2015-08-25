cmake_minimum_required(VERSION 2.8)
project(libCSD462)

# Check compiler
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(CLANG_CXX_FLAGS "-std=c++11 -m64 -O3 -funroll-loops")
    set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-narrowing")
    set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-deprecated-register")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(GCC_CXX_FLAGS "-std=gnu++11 -m64 -O3 -fopenmp -funroll-loops")
    set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -Wno-narrowing")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
endif()

# Add modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/")

# Find shared dependencies
find_package(OPENGL    REQUIRED)
find_package(FREETYPE  REQUIRED)
find_package(PKGCONFIG REQUIRED)
pkg_search_module(GLEW REQUIRED glew )
pkg_search_module(GLFW REQUIRED glfw3)

# Install settings
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/../")
set(libCSD462_BUILD_LIBS ON)
set(libCSD462_BUILD_TEST ON)

# Install rpath for OSX (requires cmake version 2.8.12+)
if(APPLE)
  if (CMAKE_VERSION VERSION_GREATER 2.8.12)
    set(CMAKE_SKIP_BUILD_RPATH  false)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH false)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)
    list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
    if("${isSystemDir}" STREQUAL "-1")
       set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    endif("${isSystemDir}" STREQUAL "-1")
  endif (CMAKE_VERSION VERSION_GREATER 2.8.12)
endif(APPLE)

# Set shared include directories
include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
)

# Set shared link directories
link_directories(
    ${GLEW_LIBRARY_DIRS}
    ${GLFW_LIBRARY_DIRS}
    ${FREETYPE_LIBRARY_DIRS}
)

# Build libraries
if (libCSD462_BUILD_LIBS)
    add_subdirectory(lib)
endif(libCSD462_BUILD_LIBS)

# Build test
if (libCSD462_BUILD_TEST)
    include_directories(lib)
    add_subdirectory(test)
endif (libCSD462_BUILD_TEST)
