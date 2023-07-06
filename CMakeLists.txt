cmake_minimum_required(VERSION 3.20)

project(breakoutGame)

option(BUILD_UNIT_TESTS "Build unit tests (default OFF)" ON)
option(CODE_COVERAGE "Enable coverage reporting (default OFF)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(conan.cmake)
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

conan_cmake_run(REQUIRES
        qt/6.1.2
        libffi/3.4.2
        BASIC_SETUP CMAKE_TARGETS
        GENERATORS cmake_find_package cmake_paths
        BUILD missing
        OPTIONS qt:shared=True
        PROFILE profile)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_library(coverage_config INTERFACE)

if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )

    target_link_options(coverage_config INTERFACE --coverage)
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

add_subdirectory(src)
add_subdirectory(include)

if (BUILD_UNIT_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()



