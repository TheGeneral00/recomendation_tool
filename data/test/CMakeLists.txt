
# Add an executable for the tests
add_executable(tests graph_test.cpp)

# Link Catch2 and the source library to the test executable
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain data_lib)
