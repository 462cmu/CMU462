# Import glfw
if(APPLE)
  add_library(glfw STATIC IMPORTED)
  set_target_properties(glfw 
    PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libglfw.a
  )
  set(GLFW_LIBRARIES glfw)
  set(GLFW_LIBRARY_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
  set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

endif(APPLE)
