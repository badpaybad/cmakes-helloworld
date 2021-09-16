cmake_minimum_required (VERSION 3.1)

#linux
#set(CMAKE_TOOLCHAIN_FILE "/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake"
#      CACHE STRING "")

#win:
set(CMAKE_TOOLCHAIN_FILE "D:/robot/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")

#cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake"

project (CMakeHelloWorld)

#version
set (CMakeHelloWorld_VERSION_MAJOR 1)
set (CMakeHelloWorld_VERSION_MINOR 1)

message("opencv lib: ${OpenCV_LIBS} ${OpenCV_DIR}")

find_package(OpenCV CONFIG REQUIRED)

add_executable(CMakeHelloWorld helloworld.cpp)

target_link_libraries(CMakeHelloWorld PRIVATE ${OpenCV_LIBS})

#install (TARGETS CMakeHelloWorld DESTINATION bin)