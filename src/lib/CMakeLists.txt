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
    CSD462 STATIC 
    ${CSD462_SOURCE} 
    ${CSD462_HEADER}
)

# link static library
set_target_properties(CSD462 PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(CSD462 PROPERTIES LINK_SEARCH_END_STATIC   1)
target_link_libraries(
    CSD462
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${FREETYPE_LIBRARIES}
)

# clang options
IF(APPLE)
    target_compile_options(CSD462 PRIVATE -Wno-constant-conversion)
ENDIF(APPLE)

# install libraries
set_target_properties(CSD462 PROPERTIES OUTPUT_NAME CSD462)
install(TARGETS CSD462 DESTINATION lib)

# install headers 
install(FILES ${CSD462_HEADER} DESTINATION include)
