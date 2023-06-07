project(UnitTests LANGUAGES CXX)

include_directories(../src)
include_directories(../include)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES
        ../src/ball.cpp
        ../src/breakout.cpp
        ../src/brick.cpp
        ../src/paddle.cpp
        tests.cpp
        )

find_package(Qt6 COMPONENTS  Widgets Test REQUIRED)

add_executable(breakout_test WIN32 ${SOURCE_FILES})

if (WIN32)
    target_link_options(breakout_test PRIVATE "/entry:mainCRTStartup")
endif()

add_test(NAME breakout_test COMMAND breakout_test)

if (WIN32 OR APPLE)
    set_tests_properties(breakout_test
            PROPERTIES
            ENVIRONMENT "PATH=${CONAN_BIN_DIRS_QT}\;$ENV{PATH}"
            )
endif()

target_link_libraries(breakout_test
        PRIVATE
        Qt6::Test
        Qt6::Widgets
        BreakoutLib
        coverage_config
        )

#if (APPLE)
#    # Since there appear to exist problems with NOT setting the RPATH when building
#    # by enabling CMAKE_KEEP_RPATH and others, we just set the libs absolute paths
#    # to the conan lib dir.
#
#    function(ChangeRPath target file new)
#        add_custom_command(TARGET breakout_test
#                POST_BUILD COMMAND
#                ${CMAKE_INSTALL_NAME_TOOL} -change @rpath/${file} ${new}/${file} $<TARGET_FILE:testMain>)
#    endfunction()
#
#    foreach(qt_lib IN LISTS CONAN_LIBS_QT)
#        ChangeRPath(breakout_test lib${qt_lib}.6.dylib ${CONAN_LIB_DIRS_QT})
#    endforeach()
#endif ()
