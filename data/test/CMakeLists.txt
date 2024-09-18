# Add an executable for the tests
add_executable(tests
    test_main.cpp
    test_graph.cpp
    # Add more test files as needed
)

# Link Catch2 and the source library to the test executable
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain data_lib)

# Add tests
add_test(NAME Tests COMMAND tests)
