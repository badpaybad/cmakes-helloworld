cmake_minimum_required (VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
#fix: error C2039: 'string_view': should c++17
set(CMAKE_CXX_STANDARD_REQUIRED on)

set( CMAKE_CXX_FLAGS " -pthread " )

#ref: https://github.com/jameskbride/cmake-hello-world
#https://vcpkg.io/en/docs/users/integration.html#cmake-integration
#https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md
#docker || command line, also use in dockerfile to build
#cmake . -DCMAKE_TOOLCHAIN_FILE="/home/dunp/work/vcpkg/scripts/buildsystems/vcpkg.cmake"
set (MY_VCPKG_INSTALLED_DIR "")
if (WIN32)
    set (MY_VCPKG_INSTALLED_DIR "C:/vcpkg")     
    if(NOT DEFINED VCPKG_TARGET_TRIPLET)
        set(VCPKG_TARGET_TRIPLET x64-windows)
    endif()
else()
    set (MY_VCPKG_INSTALLED_DIR "/vcpkg")     
    if(NOT DEFINED VCPKG_TARGET_TRIPLET)
        #set(VCPKG_TARGET_TRIPLET x64-linux)
    endif()
endif()
message("MY_VCPKG_INSTALLED_DIR: ${MY_VCPKG_INSTALLED_DIR}")

set(MY_VCPKG_INSTALLED_DIR_INCLUDE "${MY_VCPKG_INSTALLED_DIR}/installed/${VCPKG_TARGET_TRIPLET}/include")
message("MY_VCPKG_INSTALLED_DIR_INCLUDE: ${MY_VCPKG_INSTALLED_DIR_INCLUDE}")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${MY_VCPKG_INSTALLED_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project (cppsample)

#version
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 1)

# to find where lib or .dll or .so then after that should copy to root folder run if dont use vcpkg

message("CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message("")
message("PROJECT_NAME: ${PROJECT_NAME}")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message("")

find_package(OpenCV CONFIG REQUIRED)
message("OpenCV_DIR: ${OpenCV_DIR}")
message("OpenCV_LIBS: ${OpenCV_LIBS}")
message("")

#find_package(uwebsockets CONFIG REQUIRED)

find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")
#find_library(UWEBSOCKETS_LIBS uwebsockets)
message("UWEBSOCKETS_INCLUDE_DIRS: ${UWEBSOCKETS_INCLUDE_DIRS}")
message("")
#https://github.com/uNetworking/uWebSockets/issues/1043
find_package(ZLIB REQUIRED)
find_library(USOCKETS_LIB uSockets)
find_package(unofficial-libuv CONFIG REQUIRED)
find_library(LIBUV_LIB libuv)

find_package(nlohmann_json CONFIG REQUIRED)
##target_link_libraries(main PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

file (GLOB PRJ_LIBS_SOURCE 
"libs/*.h"
"libs/*.cpp"
)

add_library (PRJ_LIBS ${PRJ_LIBS_SOURCE})

#include the subdirectory containing our libs if you subdir have CMakeLists.txt
#add_subdirectory (libs)

include_directories(libs ${MY_VCPKG_INSTALLED_DIR_INCLUDE} ${UWEBSOCKETS_INCLUDE_DIRS} ${OpenCV_DIR})
#
#add_executable(${PROJECT_NAME} libs ${UWEBSOCKETS_INCLUDE_DIRS} "libs/httpserver.cpp" "program.cpp")
add_executable(${PROJECT_NAME} "program.cpp")

set (SHARED_LIBS 
     ZLIB::ZLIB
     ${USOCKETS_LIB}
     ${LIBUV_LIB}               
)

target_link_libraries(PRJ_LIBS ${OpenCV_LIBS} ${SHARED_LIBS} nlohmann_json nlohmann_json::nlohmann_json)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${SHARED_LIBS} PRJ_LIBS nlohmann_json nlohmann_json::nlohmann_json)

#copy custom resources , .dll .so if need
file(GLOB PRJ_LIBS_HEADERS "libs/*.h")

IF (WIN32)
     IF (NOT DEFINED CMAKE_TOOLCHAIN_FILE)      
          #if dont use vcpkg
          #reference dll by copy to folder run
          file (COPY "C:/opencv/build/x64/vc15/bin/" DESTINATION "Debug" FILES_MATCHING PATTERN "*.dll")
     ENDIF()
     
     #add resource file
     #file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/1.png DESTINATION "Debug")
     
     #copy own libs *.h
     file(COPY ${PRJ_LIBS_HEADERS} DESTINATION "Debug/libs")
ELSE()
     
     #copy own libs
     file(COPY ${PRJ_LIBS_HEADERS} DESTINATION "libs")
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