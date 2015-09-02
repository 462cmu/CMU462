# CMU462 library source files
set(CMU462_SOURCE
    vector2D.cpp
    vector3D.cpp
    matrix3x3.cpp
    complex.cpp
    color.cpp
    osdtext.cpp
    osdfont.c
    viewer.cpp
    base64.cpp
    tinyxml2.cpp
)

# CMU462 library header files
set(CMU462_HEADER
    CMU462.h
    vector2D.h
    vector3D.h
    matrix3x3.h
    complex.h
    color.h
    osdtext.h
    viewer.h
    base64.h
    tinyxml2.h
    renderer.h
)

# build static library
add_library(
    CMU462 STATIC 
    ${CMU462_SOURCE}
    ${CMU462_HEADER}
)

# link static library
set_target_properties(CMU462 PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(CMU462 PROPERTIES LINK_SEARCH_END_STATIC   1)
target_link_libraries(
    CMU462
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${FREETYPE_LIBRARIES}
)

# Building on mac
if (APPLE)

  # clang options
  target_compile_options(CMU462 PRIVATE -Wno-constant-conversion)
  
  # Frameworks required on osx
  target_link_libraries(CMU462  
    ${COCOA_LIBRARIES}
    ${IOKIT_LIBRARIES}
    ${COREVIDEO_LIBRARIES}
  )

endif(APPLE)

# install libCMU462
if (UNIX)
  set_target_properties(CMU462 PROPERTIES OUTPUT_NAME CMU462)
  if(APPLE)
    set_target_properties(CMU462 PROPERTIES OUTPUT_NAME CMU462_osx)
  endif(APPLE)
endif(UNIX)    
install(TARGETS CMU462 DESTINATION lib)

# install headers 
install(FILES ${CMU462_HEADER} DESTINATION include)

# install external libs
install(FILES ${GLEW_LIBRARIES} DESTINATION lib)
install(FILES ${GLFW_LIBRARIES} DESTINATION lib)

# install external headers
install(DIRECTORY ${GLEW_INCLUDE_DIRS} DESTINATION include)
install(DIRECTORY ${GLFW_INCLUDE_DIRS} DESTINATION include)
