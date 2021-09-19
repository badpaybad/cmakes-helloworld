#install vcpkg
	https://vcpkg.io/en/getting-started.html

	https://makefiletutorial.com/#getting-started

	http://wiki.ros.org/catkin/CMakeLists.txt

			set VCPKG_DEFAULT_TRIPLET=x64-windows

			VCPKG built-in triplets:
			arm-uwp
			arm64-windows
			x64-linux
			x64-osx
			x64-uwp
			x64-windows-static
			x64-windows
			x86-windows

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

				#or 
				cmake -B build -S .
				cmake --build build
				# -B build : mean all file generate into folder: build 
				# -S . : mean source file include CMakeLists.txt , current folder

				#or can create folder build
				cd build
				cmake ..
				cmake --build ..

				#cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="D:/robot/vcpkg/scripts/buildsystems/vcpkg.cmake"
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

# using cmake with custom own libs

subfolder/CMakeLists.txt eg: libs/CMakeLists.txt

		find_package(OpenCV CONFIG REQUIRED)

		add_library (Human 
		human.h
		human.cpp)

		target_link_libraries(Human ${OpenCV_LIBS})

		#install (TARGETS Hello DESTINATION bin)
		install (FILES human.h DESTINATION libs)

# visual studio code .vscode/c_cpp_properties.json
win:
				{
					"configurations": [
						{
							"name": "Win32",
							"includePath": [
								"${workspaceFolder}/**",
								//importance for #include no error
								"D:/robot/vcpkg/packages/**"
							],
							"defines": [
								"_DEBUG",
								"UNICODE",
								"_UNICODE"
							],
							"windowsSdkVersion": "10.0.18362.0",
							"compilerPath": "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\BuildTools\\VC\\Tools\\MSVC\\14.16.27023\\bin\\Hostx64\\x64\\cl.exe",
							"cStandard": "c11",
							"cppStandard": "c++14",
							"intelliSenseMode": "windows-msvc-x64"
						}
					],
					"version": 4
				}