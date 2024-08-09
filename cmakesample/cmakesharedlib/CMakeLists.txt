cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Specify the C++ standard (if needed)
set(CMAKE_CXX_STANDARD 11)

# Add the directory where your static library is located
link_directories(${CMAKE_SOURCE_DIR}/path/to/static/lib)

# Create a shared library from the static library
add_library(mylibshared SHARED
    # List the source files needed to create the shared library
    # If you don't need additional source files, you can just link the static library
    # Example: source1.cpp source2.cpp
)

# Link the static library to the shared library
target_link_libraries(mylibshared PRIVATE mylibstatic)

# Optionally, specify include directories if needed
target_include_directories(mylibshared PRIVATE ${CMAKE_SOURCE_DIR}/path/to/headers)


# project_root/
# ├── CMakeLists.txt
# ├── path/
# │   ├── to/
# │       ├── static/
# │           └── mylibstatic.a
# │       └── headers/
# │           └── your_header.h


# mkdir build
# cd build
# cmake ..
# make
