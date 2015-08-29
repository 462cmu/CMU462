# Import glfw
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw 
  PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw.a
)
set(GLFW_LIBRARIES glfw)
set(GLFW_LIBRARY_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW)
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW)

if(APPLE)
  set_target_properties(glfw 
    PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw_osx.a
  )
endif(APPLE)
