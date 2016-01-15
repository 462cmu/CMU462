link_libraries(CMU462)

include_directories("${PROJECT_SOURCE_DIR}/include")

link_libraries(
  glfw ${GLFW_LIBRARIES}
  glew ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${FREETYPE_LIBRARIES}
)

add_executable(triangle triangle.cpp)
add_executable(text text.cpp)
add_executable(event event.cpp)

# NOTE (Sky):
# the template application uses some deprecated stuff from GLUT and makes
# clang go crazy on OSX 10.9+. Someone should update that implementation.
add_executable(template template.cpp)
set_target_properties(template PROPERTIES COMPILE_FLAGS
"${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")


# Install examples
install(TARGETS triangle DESTINATION bin/examples)
