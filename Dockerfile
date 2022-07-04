# :))) use debian
#https://docs.docker.com/engine/install/ubuntu/
#FROM ubuntu:20.04
FROM mcr.microsoft.com/dotnet/runtime:6.0-focal

RUN apt-get update -y && apt-get install -y libgdiplus && rm -rf /var/lib/apt/lists/* && ln -s /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so && ln -s /usr/lib/libgdiplus.so /lib/x86_64-linux-gnu/libgdiplus.so

#RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null

#RUN apt-get install ffmpeg -y
RUN apt-get update --fix-missing -y && apt-get install -y nano htop git curl zip unzip tar g++ cmake build-essential libsm6 libxext6 libgl1-mesa-glx libgl1 pkg-config libgtk-3-dev python3 python3-pip

#upgrade cmake to 3.2x
RUN pip3 install cmake --upgrade
RUN cmake --version
#EXPOSE 9004
#EXPOSE 443 

#cause in cmakelist.txt set (MY_VCPKG_INSTALLED_DIR "/vcpkg")   
RUN git clone --progress --verbose https://github.com/Microsoft/vcpkg.git
RUN chmod -R 777 ./vcpkg

RUN ./vcpkg/bootstrap-vcpkg.sh
#RUN ./vcpkg/vcpkg install pthreads:x64-linux
#RUN ./vcpkg/vcpkg install opencv[core,contrib]
RUN ./vcpkg/vcpkg install zlib
RUN ./vcpkg/vcpkg install libuv
RUN ./vcpkg/vcpkg install usockets
RUN ./vcpkg/vcpkg install uwebsockets:x64-linux
RUN ./vcpkg/vcpkg install nlohmann-json:x64-linux
RUN ./vcpkg/vcpkg install ncurses

RUN mkdir -p /app/
RUN mkdir -p /app/libs/

COPY ["libs/*.h","/app/libs/"]
#COPY libs/*.hpp /app/libs/
COPY ["libs/*.cpp","/app/libs/"]
#COPY libs/*.cxx /app/libs/
COPY ["libs/*.txt","/app/libs/"]

#COPY ["*.h","/app/"]
#COPY *.hpp /app/
COPY ["*.cpp","/app/"]
#COPY *.cxx /app/
COPY ["*.txt","/app/"]
COPY ["1.png","/app/"]

WORKDIR /app
RUN chmod -R 777 /app
# ##CMAKE_TOOLCHAIN_FILE in CMakeList.txt
RUN cmake /app -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake"
RUN cmake --build /app

#clean up
RUN apt-get -y clean \
    && rm -rf /var/lib/apt/lists/*
RUN rm -rf /vcpkg

RUN rm /app/libs/*.cpp
RUN rm /app/libs/*.txt
RUN rm /app/*.cpp
RUN rm /app/*.txt
RUN rm -rf /app/CMakeFiles
RUN rm /app/Makefile
RUN rm /app/cmake_install.cmake

RUN chmod 777 ./CMakeHelloWorld
EXPOSE 9004
CMD ["./CMakeHelloWorld"] 

# #uwebsokets set listener __port= 9004 in program.cpp
# #docker build -f Dockerfile -t vcpkgtest .
# #docker run -it --rm -p 9004:9004 --name vcpkgtest_9004 vcpkgtest 