# minecraft-server-stop
A simple C++ program to automatically stop my EC2 Minecraft server

## Prerequisites
* Minimum CMake version 3.0.2
* Sets compile flag -Wall and -std=c++11 in CMakeLists.txt

## Build
```
cd [project_dir]
mkdir build
cd build
cmake ..
make
```

## Notes
* No make install at this point
* `cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1` to generate compile_commands.json for libclang consumption
