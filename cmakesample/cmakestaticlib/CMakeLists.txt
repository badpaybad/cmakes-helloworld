cmake_minimum_required(VERSION 3.10)
project(MyStaticLibrary)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add your source files
set(SOURCES
    example.cpp
    utils.cpp
)

# Create a static library
add_library(mylibrary STATIC ${SOURCES})

# Optionally, specify include directories
target_include_directories(mylibrary PUBLIC ${CMAKE_SOURCE_DIR}/include)