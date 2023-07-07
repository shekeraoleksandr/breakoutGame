[![ubuntu](https://github.com/shekeraoleksandr/breakoutGame/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/shekeraoleksandr/breakoutGame/actions/workflows/ubuntu.yml)
# C++ Conan CMake Qt6 Breakout game
This project uses C++20 and Qt 6.1.2.

* `[x]` Using Qt6 with CMake and Conan
* `[x]` Using a custom static library
* `[x]` Github actions to build on Ubuntu
* `[x]` A unit test environment

# Building

First, we clone the GitHub repository:

```bash
git clone https://github.com/shekeraoleksandr/breakoutGame.git
```

Then create a build folder inside of the repository's folder and navigate into it:

```bash
cd breakoutGame && mkdir build && cd build
```

Once we've created the build directory, we can run Conan and CMake in one step:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

In this case, we have configured our build system to compile debug versions of the binaries. Now we can build with the following command:

```bash
cmake --build .
```

To execute the program:
```bash
./bin/breakoutSrc 
```

# Details
> **Warning**:
> Qt6 works only with the Conan version < 2.0.

To reinstall Conan:
```bash
pip install --force-reinstall -v "conan==1.60.0"
```
## Using Qt6 with CMake and Conan
The only way I could get Qt6 to work with Conan and CMake was by including the `conan.cmake` file from: https://github.com/conan-io/cmake-conan

The main problems that I ran into were:

### Wayland conflict:
```bash
ERROR: Conflict in wayland/1.21.0:
'wayland/1.21.0' requires 'libffi/3.4.4' while 'glib/2.73.0' requires 'libffi/3.4.3'.
```

To fix it I had to specify the version of `libffi` I wanted to use in the root *CMakeLists.txt*:

```cmake
conan_cmake_run(REQUIRES
        qt/6.1.2
        libffi/3.4.2
    ...
```

### Package manager mode install:

```bash
xorg/system: ERROR: while executing system_requirements(): 
System requirements: 'libx11-xcb-dev, ...' are missing but can't install because tools.system.package_manager:mode is 'check'.
Please update packages manually or set 'tools.system.package_manager:mode' to 'install' in the [conf] section of the profile, 
or in the command line using '-c tools.system.package_manager:mode=install'
```

To fix it I had to add `tools.system.package_manager:mode=install` in the conf section of my profile, in my case profiles are located in `/home/user/.conan/profiles/` but your path can be different.
Also I created my profile using `conan_cmake_profile` in the root *CMakeLists.txt*:

```cmake
conan_cmake_profile(FILEPATH    "${CMAKE_BINARY_DIR}/profile"
                    SETTINGS    os=Linux
                                os_build=Linux
                                arch=x86_64
                                arch_build=x86_64
                                compiler=gcc
                                compiler.version=9
                                compiler.libcxx=libstdc++11
                                build_type=Release
                    OPTIONS     qt:shared=True
                    CONF        "tools.system.package_manager:mode=install"
                                "tools.system.package_manager:sudo=True")    
```
To use this profile over default I added `PROFILE profile` to the root *CMakeLists.txt*:

```cmake
conan_cmake_run(REQUIRES
        ...
        PROFILE profile)
```

### Xcb plugin not found:

```bash
qt.qpa.xcb: could not connect to display
qt.qpa.plugin: Could not load the Qt platform plugin "xcb" in "" even though it was found.
This application failed to start because no Qt platform plugin could be initialized. Reinstalling the application may fix this problem.
```

There may be several solutions to this problem, discussed [here](https://askubuntu.com/questions/308128/failed-to-load-platform-plugin-xcb-while-launching-qt5-app-on-linux-without). 

I personally added `qt:shared=True` to the `OPTIONS` section of the profile that creates in the root *CMakeLists.txt*:

```cmake
conan_cmake_profile(FILEPATH    "${CMAKE_BINARY_DIR}/profile"
                    ...
                    OPTIONS     qt:shared=True
                    ...
```

It can also be added to the `conan_cmake_run`:

```cmake
conan_cmake_run(REQUIRES
        ...
        OPTIONS qt:shared=True
        ...
```

## Using a custom library
The library is called `BreakoutLib` it exist `include/`.

Even though no linking is actually done when building the library by itself, this line must still be included in the library's CMake file:

```cmake
target_link_libraries(MyLib PRIVATE
    Qt6::Core
)
```

## Unit Tests and GitHub Actions
I could only get Qt6 to build on Github Actions if I used `ubuntu-latest`.

I faced the `xcb` error and to solve it I specified a virtual display for the CTest execution.

```yaml
- name: Install xvfb
  run: sudo apt install xvfb

- name: Run Tests with xvfb
  run: xvfb-run ctest --rerun-failed --output-on-failure

```
