# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.11)

# Name of the project
project(GraphProcessing)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# FetchContent module for Catch2
include(FetchContent)

# Fetch Catch2 from GitHub
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # Specify the latest version (or replace with a version you want)
)

# Make Catch2 available
FetchContent_MakeAvailable(catch2)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)

# Enable testing
enable_testing()
