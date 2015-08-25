# Renderer Test
add_executable( 
    renderer_test
    renderer.cpp
)

target_link_libraries(
    renderer_test
    CSD462Shared
)

install(TARGETS renderer_test DESTINATION bin/renderer_test)