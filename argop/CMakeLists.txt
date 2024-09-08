cmake_minimum_required(VERSION 3.5)

# Project name
project(argop C)

# Set the version of the library
set(LIBRARY_VERSION 2.0.0)
set(SO_VERSION 2)

# Specify the source files
set(SOURCES argop.c)

# Add the shared library target
add_library(argop SHARED ${SOURCES})

# Set the versioning for the library
set_target_properties(argop PROPERTIES
    VERSION ${LIBRARY_VERSION}
    SOVERSION ${SO_VERSION}
    POSITION_INDEPENDENT_CODE ON # Equivalent to -fPIC
)

# Set the output name of the library
set_target_properties(argop PROPERTIES
    OUTPUT_NAME "argop"
)

# Install the library to a specific directory (optional)
install(TARGETS argop
    LIBRARY DESTINATION /usr/lib
)
