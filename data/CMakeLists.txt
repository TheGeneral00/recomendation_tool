cmake_minimum_required(VERSION 3.11)
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include Catch2 using FetchContent
include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # Or the latest version tag
)

FetchContent_MakeAvailable(catch2)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)

# Enable testing
enable_testing()
