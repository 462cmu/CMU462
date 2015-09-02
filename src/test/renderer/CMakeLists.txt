# Renderer Test
add_executable( 
    renderer_test
    renderer.cpp
)

target_link_libraries(
    renderer_test
    CMU462
)

install(TARGETS renderer_test DESTINATION bin)