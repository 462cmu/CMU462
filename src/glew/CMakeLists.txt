# Import glew
add_library(glew STATIC IMPORTED)
set_target_properties(glew 
  PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglew.a
)
set(GLEW_LIBRARIES glew)
set(GLEW_LIBRARY_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLEW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(APPLE)
  set_target_properties(glew 
    PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglew_osx.a
  )
endif(APPLE)
