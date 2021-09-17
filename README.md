#install vcpkg
	https://vcpkg.io/en/getting-started.html

	https://makefiletutorial.com/#getting-started

# apt install

				apt install update && apt-get install -y libgdiplus && rm -rf /var/lib/apt/lists/* && ln -s /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so && ln -s /usr/lib/libgdiplus.so /lib/x86_64-linux-gnu/libgdiplus.so
				apt install -y g++
				apt install -y build-essential
				apt install -y libgtk2.0-dev && pkg-config
				apt install -y ffmpeg libsm6 libxext6 libgl1-mesa-glx libgl1
				apt install libgtk2.0-dev
				apt install pkg-config
				apt install libgtk-3-dev
# create MakeLists.txt

# command

				./vcpkg install opencv

				cmake .

				cmake --build .

# check your vcpkg path in MakeLists.txt CMAKE_TOOLCHAIN_FILE


# code sample with opencv

https://docs.opencv.org/4.5.2/examples.html

# opencv -DWITH_GTK=ON

The problem is vcpkg passes in the build option -DWITH_GTK=OFF when building OpenCV. The open issue: https://github.com/microsoft/vcpkg/issues/12621

The workaround is the following:

    edit the file vcpkg/ports/opencv4/portfile.cmake
    find the line that says -DWITH_GTK=OFF and change it to say -DWITH_GTK=ON
    run ./vcpkg remove opencv4
    run sudo apt-get install libgtk2.0-dev pkg-config
    reinstall OpenCV with ./vcpkg install opencv4 or whichever vcpkg command you used

