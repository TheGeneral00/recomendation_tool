#Define library or executable
add_library(data_lib STATIC
    data_processing.cpp
    )

# Link Catch2 and source library to the test executable
target_link_libraries(tests PRIVATE Ctach2::Catch2WithMain data_lib)

# Include directories for headers
target_include_directories(data_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#add tests
add_test(NAME Tests COMMAND tests)
