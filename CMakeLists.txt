cmake_minimum_required (VERSION 3.1)
#ref: https://github.com/jameskbride/cmake-hello-world
#https://vcpkg.io/en/docs/users/integration.html#cmake-integration

#docker || command line, also use in dockerfile to build
#cmake . -DCMAKE_TOOLCHAIN_FILE="/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake"

IF (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
     IF (WIN32)
          #win:
          set(CMAKE_TOOLCHAIN_FILE "D:/robot/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
     ELSE()
          #linux
          set(CMAKE_TOOLCHAIN_FILE "/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
     ENDIF()
ENDIF()

project (CMakeHelloWorld)

#version
set (CMakeHelloWorld_VERSION_MAJOR 1)
set (CMakeHelloWorld_VERSION_MINOR 1)

#include the subdirectory containing our libs
add_subdirectory (libs)
include_directories(libs)

# to find where lib or .dll or .so then after that should copy to root folder run if dont use vcpkg
find_package(OpenCV CONFIG REQUIRED)

message("VCPKG_ROOT: ${VCPKG_ROOT}")
message("CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message("WIN32: ${WIN32} #1: true, 0: false")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message("OpenCV_LIBS: ${OpenCV_LIBS}")
message("OpenCV_DIR: ${OpenCV_DIR}")

add_executable(CMakeHelloWorld libs program.cpp)

target_link_libraries(CMakeHelloWorld Human ${OpenCV_LIBS})

#copy custom resources , .dll .so if need
file(GLOB MY_PUBLIC_HEADERS "libs/*.h")

IF (WIN32)
     IF (NOT DEFINED CMAKE_TOOLCHAIN_FILE)      
          #if dont use vcpkg
          #reference dll           
          file (COPY "C:/opencv/build/x64/vc15/bin/" DESTINATION "Debug" FILES_MATCHING PATTERN "*.dll")
     ENDIF()
     
     #add resource file
     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/1.png DESTINATION "Debug")
     
     #copy own libs *.h
     file(COPY ${MY_PUBLIC_HEADERS} DESTINATION "Debug/libs")
ELSE()
     
     #copy own libs
     file(COPY ${MY_PUBLIC_HEADERS} DESTINATION "libs")
ENDIF()

