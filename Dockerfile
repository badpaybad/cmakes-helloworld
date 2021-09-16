# :))) use debian
FROM mcr.microsoft.com/dotnet/aspnet:3.1 
RUN apt-get update && apt-get install -y libgdiplus && rm -rf /var/lib/apt/lists/* && ln -s /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so && ln -s /usr/lib/libgdiplus.so /lib/x86_64-linux-gnu/libgdiplus.so
RUN apt-get update -y
RUN apt-get install htop -y
RUN apt-get install -y git curl zip unzip tar 
RUN apt-get install -y g++ cmake build-essential 
RUN apt-get install -y ffmpeg libsm6 libxext6 libgl1-mesa-glx libgl1
RUN apt-get install -y libgtk2.0-dev && pkg-config
EXPOSE 80
#EXPOSE 443

RUN git clone --progress --verbose https://github.com/Microsoft/vcpkg.git
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ./vcpkg/vcpkg intall opencv

COPY helloworld.cpp /app/
COPY CMakeLists.txt /app/

RUN cmake /app -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake"
RUN cmake --build /app
CMD ["./app/CMakeHelloWorld"] 


#docker build -f Dockerfile -t vcpkgtest .
#docker run -it --rm -p 9003:80 --name vcpkgtest_9003 vcpkgtest 