cmake_minimum_required (VERSION 3.1)
#ref: https://github.com/jameskbride/cmake-hello-world
#https://vcpkg.io/en/docs/users/integration.html#cmake-integration
#https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md
#docker || command line, also use in dockerfile to build
#cmake . -DCMAKE_TOOLCHAIN_FILE="/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake"

set (_VCPKG_INSTALLED_DIR "")
IF (WIN32)     
     IF ( NOT DEFINED VCPKG_TARGET_TRIPLET)
          set(VCPKG_TARGET_TRIPLET "x64-windows")
     ENDIF()
     set (_VCPKG_INSTALLED_DIR "D:/robot/vcpkg")     
     message("win: ${VCPKG_TARGET_TRIPLET}")
     # IF ( NOT DEFINED CMAKE_TOOLCHAIN_FILE)
     #      set(CMAKE_TOOLCHAIN_FILE "D:/robot/vcpkg/scripts/buildsystems/vcpkg.cmake")
     # ENDIF()
ELSE()
     IF ( NOT DEFINED VCPKG_TARGET_TRIPLET)
          set(VCPKG_TARGET_TRIPLET "x64-linux")
     ENDIF()
     message("linux: ${VCPKG_TARGET_TRIPLET}")
     set (_VCPKG_INSTALLED_DIR "/home/dunp/work/vcpkg")
     # IF ( NOT DEFINED CMAKE_TOOLCHAIN_FILE)
     #      set(CMAKE_TOOLCHAIN_FILE "/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake")
     # ENDIF()
ENDIF()

IF ( NOT DEFINED CMAKE_TOOLCHAIN_FILE)
     set(CMAKE_TOOLCHAIN_FILE "${_VCPKG_INSTALLED_DIR}/scripts/buildsystems/vcpkg.cmake")
ENDIF()

set (VCPKG_INSTALLED_INCLUDE_DIR "${_VCPKG_INSTALLED_DIR}/installed/${VCPKG_TARGET_TRIPLET}/include")

project (CMakeHelloWorld)

#version
#set (CMakeHelloWorld_VERSION_MAJOR 1)
#set (CMakeHelloWorld_VERSION_MINOR 1)

# to find where lib or .dll or .so then after that should copy to root folder run if dont use vcpkg

message("")
message("PROJECT_NAME: ${PROJECT_NAME}")
message("CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message("VCPKG_INSTALLED_INCLUDE_DIR: ${VCPKG_INSTALLED_INCLUDE_DIR}")
message("")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message("")

find_package(OpenCV CONFIG REQUIRED)
message("OpenCV_DIR: ${OpenCV_DIR}")
message("OpenCV_LIBS: ${OpenCV_LIBS}")
message("")

find_package(uwebsockets)
message("UWEBSOCKETS_INCLUDE_DIRS: ${UWEBSOCKETS_INCLUDE_DIRS}")
message("UWEBSOCKETS_LIBS: ${UWEBSOCKETS_LIBS}")
message("")
#include the subdirectory containing our libs
add_subdirectory (libs)

include_directories(libs ${VCPKG_INSTALLED_INCLUDE_DIR} ${UWEBSOCKETS_INCLUDE_DIRS} ${OpenCV_DIR})
#
#add_executable(${PROJECT_NAME} libs ${UWEBSOCKETS_INCLUDE_DIRS} "libs/httpserver.cpp" "program.cpp")
add_executable(${PROJECT_NAME} libs "program.cpp")

target_link_libraries(${PROJECT_NAME} Human ${OpenCV_LIBS} ${UWEBSOCKETS_LIBS})

#copy custom resources , .dll .so if need
file(GLOB MY_PUBLIC_HEADERS "libs/*.h")

IF (WIN32)
     IF (NOT DEFINED CMAKE_TOOLCHAIN_FILE)      
          #if dont use vcpkg
          #reference dll by copy to folder run
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

# add_custom_target(clean-cmake-files
#    COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
# )

# set(cmake_generated ${CMAKE_BINARY_DIR}/CMakeCache.txt
#                     ${CMAKE_BINARY_DIR}/cmake_install.cmake
#                     ${CMAKE_BINARY_DIR}/Makefile
#                     ${CMAKE_BINARY_DIR}/CMakeFiles
# )


# foreach(file ${cmake_generated})

#   if (EXISTS ${file})
#      file(REMOVE_RECURSE ${file})
#      file(REMOVE ${file})
#   endif()

# endforeach(file)