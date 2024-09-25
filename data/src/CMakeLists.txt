#Define library or executable
add_library(data_lib STATIC
    graph.h
    )

# Link Catch2 and source library to the test executable
target_link_libraries(data_lib PRIVATE Catch2::Catch2WithMain)

# Include directories for headers
target_include_directories(data_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# add subdir for wrappers
add_subdirectory(wrappers)
