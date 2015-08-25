# Text Test
add_executable( 
    text_test 
    text.cpp
)

target_link_libraries(
    text_test
    CSD462Shared
)

install(TARGETS text_test DESTINATION bin/text_test)
