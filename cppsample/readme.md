# basic c++

learn basic first

                https://www.cplusplus.com/doc/tutorial/

# setup enviroment

vcpkg.io

                https://vcpkg.io/en/getting-started.html

                git clone https://github.com/Microsoft/vcpkg.git

                //win:
                vcpkg/bootstrap-vcpkg.bat
                //linux:
                ./vcpkg/bootstrap-vcpkg.sh

vcpkg pre install package

                vcpkg install libuv, opencv, opencv[core,contrib], uwebsockets, nlohmann-json
                
                //we may need add :x64-windows or :x64-linux ...
                //eg: vcpkg install opencv:x64-windows

cmake

                https://cmake.org/download/ Latest Release (3.21.3)

ide

                https://code.visualstudio.com/download

use cmake with makefile

                cppsample\CMakeLists.txt

MY_VCPKG_INSTALLED_DIR in CMakeLists.txt have to change your own dir vcpkg git clone above

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

cmake command 

                cmake -B build -S .
                // -B folderToCreateFileBuild
                // -S source code (.h .cpp ) with file CMakeLists.txt
                // . (dot) current dir, or your full path folder

                cmake --build .
                // . (dot) current dir, or your full path folder

vs code with cmake extension

                //open and do command
                Ctrl + Shift + P 
                //type: CMake: ... ( build, debug, run, config ...)

# happy coding

you can use vs code to debug or run ...

