cmake_minimum_required (VERSION 3.1)
#ref: https://github.com/jameskbride/cmake-hello-world
#https://vcpkg.io/en/docs/users/integration.html#cmake-integration
#linux
set(CMAKE_TOOLCHAIN_FILE "/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")

#win:
#set(CMAKE_TOOLCHAIN_FILE "D:/robot/vcpkg/scripts/buildsystems/vcpkg.cmake"
#      CACHE STRING "")

#cmake . -DCMAKE_TOOLCHAIN_FILE="/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake"

project (CMakeHelloWorld)

#version
set (CMakeHelloWorld_VERSION_MAJOR 1)
set (CMakeHelloWorld_VERSION_MINOR 1)

message("opencv lib: ${OpenCV_LIBS} ${OpenCV_DIR}")

find_package(OpenCV CONFIG REQUIRED)

add_executable(CMakeHelloWorld helloworld.cpp)

target_link_libraries(CMakeHelloWorld PRIVATE ${OpenCV_LIBS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/1.png
     #DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
     DESTINATION "Debug"
     )

#install (TARGETS CMakeHelloWorld DESTINATION bin)
