link_libraries(CMU462)

include_directories("${PROJECT_SOURCE_DIR}/src")

link_libraries(
  glfw ${GLFW_LIBRARIES}
  glew ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${FREETYPE_LIBRARIES}
)

# Triangle drawer
add_executable(triangle triangle.cpp)

# Install examples
install(TARGETS triangle DESTINATION bin/examples)