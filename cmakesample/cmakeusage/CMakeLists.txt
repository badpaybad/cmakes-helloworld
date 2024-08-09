cmake_minimum_required(VERSION 3.10)
project(MyExecutable)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add the directory where your shared library is located
link_directories(${CMAKE_SOURCE_DIR}/path/to/shared/lib)

# Add the source files for your executable
add_executable(my_executable main.cpp)

# Link the shared library to your executable
target_link_libraries(my_executable PRIVATE mylibshared)

# Optionally, specify include directories if needed
target_include_directories(my_executable PRIVATE ${CMAKE_SOURCE_DIR}/path/to/headers)


# project_root/
# ├── CMakeLists.txt
# ├── main.cpp
# ├── path/
# │   ├── to/
# │       └── shared/
# │           └── libmylibshared.so
# │       └── headers/
# │           └── your_header.h
