// Check if the C++ Compiler is Installed
g++ --version

// if not proceed with this download gcc
sudo apt-get update
sudo apt-get install build-essential

// returns with the library where gcc can be found for example /usr/bin/g++
which g++

// set the gcc path variable
export CXX=/usr/bin/g++

// Check if pkg-config is Installed
pkg-config --version

// install pkg-config
sudo apt-get update
sudo apt-get install pkg-config

// cd into the external folder
cd {PATH_TO_PROJECT}/modeller/external

// clone the imgui repo
git clone https://github.com/ocornut/imgui.git

// install glfw
sudo apt-get update
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev

// if there are this error: 
/*
/snap/clion/248/bin/cmake/linux/x64/bin/cmake --build /home/levi/CLionProjects/modeller/cmake-build-debug --target modeller -- -j 6
gmake: /snap/clion/246/bin/cmake/linux/x64/bin/cmake: No such file or directory
gmake: *** [Makefile:625: cmake_check_build_system] Error 127
*/
// change the directory from /snap/clion/246/bin/cmake/linux/x64/bin/cmake to /snap/clion/248/bin/cmake/linux/x64/bin/cmake
// under the File -> Settings (Preferences for macOS) -> Build, Execution, Deployment -> Toolchains -> CMake