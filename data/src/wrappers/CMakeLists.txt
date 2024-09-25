# Find Python and pybind11
find_package(Python REQUIRED COMPONENTS Interpreter Development)

# Set the path to the parent directory containing the virtual environment
set(VENV_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../venv")

# Update the CMAKE_PREFIX_PATH to include the site-packages directory of the venv
set(CMAKE_PREFIX_PATH "${VENV_PATH}/lib/python${Python_VERSION}/site-packages")

# Locate the pybind11 CMake directory within the virtual environment
execute_process(
    COMMAND ${VENV_PATH}/bin/python -m pybind11 --cmakedir
    OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Inform CMake about the location of pybind11
set(pybind11_DIR ${PYBIND11_CMAKE_DIR})

# Find the pybind11 package
find_package(pybind11 REQUIRED)

# Specify output directory for the shared library
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Create shared library for Python bindings
pybind11_add_module(graph_module graph_wrapper.cpp)
# Debug message to confirm target creation
message(STATUS "Creating graph_module target.")

# Link the bindings with pybind11 and your data library (data_lib)
target_link_libraries(graph_module PRIVATE data_lib)

# Set output directory for Python module
set_target_properties(graph_module PROPERTIES
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
)
