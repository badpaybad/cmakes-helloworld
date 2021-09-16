#install vcpkg
https://vcpkg.io/en/getting-started.html

# apt install

apt install update && apt-get install -y libgdiplus && rm -rf /var/lib/apt/lists/* && ln -s /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so && ln -s /usr/lib/libgdiplus.so /lib/x86_64-linux-gnu/libgdiplus.so
apt install -y g++
apt install -y build-essential
apt install -y libgtk2.0-dev && pkg-config
apt install -y ffmpeg libsm6 libxext6 libgl1-mesa-glx libgl1

# create MakeLists.txt

# command

				./vcpkg install opencv

				cmake .

				cmake --build .

# check your vcpkg path in MakeLists.txt CMAKE_TOOLCHAIN_FILE


# code sample with opencv

https://docs.opencv.org/4.5.2/examples.html
