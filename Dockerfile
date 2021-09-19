# :))) use debian
FROM mcr.microsoft.com/dotnet/runtime:3.1 
RUN apt-get update && apt-get install -y libgdiplus && rm -rf /var/lib/apt/lists/* && ln -s /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so && ln -s /usr/lib/libgdiplus.so /lib/x86_64-linux-gnu/libgdiplus.so
RUN apt-get update -y
RUN apt-get install htop -y
RUN apt-get install -y git curl zip unzip tar 
RUN apt-get install -y g++ cmake build-essential 
RUN apt-get install -y ffmpeg libsm6 libxext6 libgl1-mesa-glx libgl1
RUN apt-get install -y pkg-config
RUN apt install -y libgtk-3-dev
#EXPOSE 9004
#EXPOSE 443 

RUN git clone --progress --verbose https://github.com/Microsoft/vcpkg.git
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ./vcpkg/vcpkg install opencv
RUN ./vcpkg/vcpkg install pthreads:x64-linux
RUN ./vcpkg/vcpkg install uwebsockets:x64-linux

COPY libs/*.h /app/libs/
COPY libs/*.hpp /app/libs/
COPY libs/*.cpp /app/libs/
COPY libs/*.cxx /app/libs/
COPY libs/*.txt /app/libs/

COPY *.h /app/
COPY *.hpp /app/
COPY *.cpp /app/
COPY *.cxx /app/
COPY *.txt /app/
COPY 1.png /app/

WORKDIR /app
RUN cmake . -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake"
RUN cmake --build .
#RUN rm -rf /vcpkg
CMD ["./CMakeHelloWorld"] 


#docker build -f Dockerfile -t vcpkgtest .
#docker run -it --rm -p 9004:9004 --name vcpkgtest_9004 vcpkgtest 