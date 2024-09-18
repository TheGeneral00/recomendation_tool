#Define library or executable
add_library(data_lib STATIC
    new_graph.h
    )

# Link Catch2 and source library to the test executable
target_link_libraries(data_lib PRIVATE Catch2::Catch2WithMain tests)

# Include directories for headers
target_include_directories(data_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#add tests
add_test(NAME Test COMMAND test)
