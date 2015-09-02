# Text Test
add_executable( 
    text_test 
    text.cpp
)

target_link_libraries(
    text_test
    CMU462
)

install(TARGETS text_test DESTINATION bin)
