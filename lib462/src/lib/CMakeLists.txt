# CSD462 library source files
set(CSD462_SOURCE
    vector2D.cpp
    vector3D.cpp
    matrix3x3.cpp
    complex.cpp
    color.cpp
    viewport.cpp
    osdtext.cpp
    osdfont.c
    viewer.cpp
    tinyxml2.cpp
)

# CSD462 library header files
set(CSD462_HEADER
    CSD462.h
    vector2D.h
    vector3D.h
    matrix3x3.h
    complex.h
    color.h
    renderer.h
    viewport.h
    osdtext.h
    viewer.h
    tinyxml2.h
)

# build static library
add_library(
    CSD462Static STATIC 
    ${CSD462_SOURCE} 
    ${CSD462_HEADER}
)

# build shared library
add_library(
    CSD462Shared SHARED 
    ${CSD462_SOURCE} 
    ${CSD462_HEADER}
)

# link targets
target_link_libraries(
    CSD462Static
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${FREETYPE_LIBRARIES}
)

target_link_libraries(
    CSD462Shared
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${FREETYPE_LIBRARIES}
)

# compiler flags
IF(APPLE)
    target_compile_options(CSD462Static PRIVATE -Wno-constant-conversion)
    target_compile_options(CSD462Shared PRIVATE -Wno-constant-conversion)
ENDIF(APPLE)

# install libraries
set_target_properties(CSD462Static PROPERTIES OUTPUT_NAME CSD462)
set_target_properties(CSD462Shared PROPERTIES OUTPUT_NAME CSD462)
install(TARGETS CSD462Static DESTINATION lib)
install(TARGETS CSD462Shared DESTINATION lib)

# install headers 
install(FILES ${CSD462_HEADER} DESTINATION include)
