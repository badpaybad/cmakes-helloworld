# choose your language and ignore other

except c/c++ have to read carefully 

# pysample.Dockerfile

main code uvicorn, fastapi pysample.py 

				docker build -f pysample.Dockerfile -t pysample .
				docker run -it --rm -p 9002:8001 --name pysample_9002 pysample

# phpsample.Dockerfile

main code phpsample.php , simple mvc with cmd: php -S 0.0.0.0:9000 phpsample.php :D 
need someone create for laravel, lumen ...

				docker build -f phpsample.Dockerfile -t phptest .
				docker run -it --rm -p 9005:9000 --name phptest_9005 phptest 


# c# csharp /Mnvn.WebAppDockerTest/Dockerfile

main code go to folder Mnvn.WebAppDockerTest check Dockerfile

				docker build -t mnvntest .
				docker run -it --rm -p 5000:80 --name mnvntest_5000 mnvntest


# c/c++ Dockerfile

c/c++ quite complex, you need to know about vcpkg.io and cmake with how to create makelists.txt

				docker build -f Dockerfile -t vcpkgtest .
				docker run -it --rm -p 9004:9004 --name vcpkgtest_9004 vcpkgtest 

### install vcpkg
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

### apt install

				apt install update && apt-get install -y libgdiplus && rm -rf /var/lib/apt/lists/* && ln -s /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so && ln -s /usr/lib/libgdiplus.so /lib/x86_64-linux-gnu/libgdiplus.so
				apt install -y g++
				apt install -y build-essential
				apt install -y libgtk2.0-dev && pkg-config
				apt install -y ffmpeg libsm6 libxext6 libgl1-mesa-glx libgl1
				apt install libgtk2.0-dev
				apt install pkg-config
				apt install libgtk-3-dev

				sudo apt-get install -y software-properties-common
				sudo add-apt-repository ppa:ubuntu-toolchain-r/test
				sudo apt update
				sudo apt install g++-7 -y
				$ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7
### create MakeLists.txt

have to upgrade to cmake 3.2xxx

				sudo apt purge --auto-remove cmake
				wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
				sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
				sudo apt update
				sudo apt install cmake

### command

				./vcpkg install opencv[core,cuda,contrib]
				./vcpkg install uwebsockets

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
### check your vcpkg path in MakeLists.txt CMAKE_TOOLCHAIN_FILE


### code sample with opencv

https://docs.opencv.org/4.5.2/examples.html

### opencv -DWITH_GTK=ON

The problem is vcpkg passes in the build option -DWITH_GTK=OFF when building OpenCV. The open issue: https://github.com/microsoft/vcpkg/issues/12621

The workaround is the following:

    edit the file vcpkg/ports/opencv4/portfile.cmake
    find the line that says -DWITH_GTK=OFF and change it to say -DWITH_GTK=ON
    run ./vcpkg remove opencv4
    run sudo apt-get install libgtk2.0-dev pkg-config
    reinstall OpenCV with ./vcpkg install opencv4 or whichever vcpkg command you used

### using cmake with custom own libs

subfolder/CMakeLists.txt eg: libs/CMakeLists.txt

		find_package(OpenCV CONFIG REQUIRED)

		add_library (Human 
		human.h
		human.cpp)

		target_link_libraries(Human ${OpenCV_LIBS})

		#install (TARGETS Hello DESTINATION bin)
		install (FILES human.h DESTINATION libs)

### visual studio code .vscode/c_cpp_properties.json
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
				
# image figure out mindset

![dockerfile sample](https://user-images.githubusercontent.com/6204507/134214584-791ca0ca-c85c-44b1-b7c5-a1e1c371eacb.jpg)
