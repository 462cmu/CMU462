# Import glew
if(APPLE)
  add_library(glew STATIC IMPORTED)
  set_target_properties(glew 
    PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libglew.a
  )
  set(GLEW_LIBRARIES glew)
  set(GLEW_LIBRARY_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
  set(GLEW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

endif(APPLE)
