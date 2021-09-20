# :))) use debian
#https://docs.docker.com/engine/install/ubuntu/
FROM mcr.microsoft.com/dotnet/runtime:3.1 
RUN apt-get update && apt-get install -y libgdiplus && rm -rf /var/lib/apt/lists/* && ln -s /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so && ln -s /usr/lib/libgdiplus.so /lib/x86_64-linux-gnu/libgdiplus.so
RUN apt-get update -y
#RUN apt-get install ffmpeg -y
RUN apt-get install -y git curl zip unzip tar 
RUN apt-get install -y g++ cmake build-essential 
RUN apt-get install -y libsm6 libxext6 libgl1-mesa-glx libgl1
RUN apt-get install -y pkg-config
RUN apt install -y libgtk-3-dev
#EXPOSE 9004
#EXPOSE 443 

RUN git clone --progress --verbose https://github.com/Microsoft/vcpkg.git
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ./vcpkg/vcpkg install pthreads:x64-linux
RUN ./vcpkg/vcpkg install opencv
RUN ./vcpkg/vcpkg install zlib
RUN ./vcpkg/vcpkg install libuv
RUN ./vcpkg/vcpkg install usockets
RUN ./vcpkg/vcpkg install uwebsockets:x64-linux
RUN ./vcpkg/vcpkg install nlohmann-json:x64-linux

RUN mkdir -p /app
RUN mkdir -p /app/libs

COPY ["libs/*.h","/app/libs/"]
#COPY libs/*.hpp /app/libs/
COPY ["libs/*.cpp","/app/libs/"]
#COPY libs/*.cxx /app/libs/
COPY ["libs/*.txt","/app/libs/"]

COPY ["*.h","/app/"]
#COPY *.hpp /app/
COPY ["*.cpp","/app/"]
#COPY *.cxx /app/
COPY ["*.txt","/app/"]
COPY ["1.png","/app/"]

WORKDIR /app
RUN cmake . -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake"
RUN cmake --build .
#RUN rm -rf /vcpkg
CMD ["./CMakeHelloWorld"] 

#uwebsokets set listener __port= 9004 in program.cpp
#docker build -f Dockerfile -t vcpkgtest .
#docker run -it --rm -p 9004:9004 --name vcpkgtest_9004 vcpkgtest 