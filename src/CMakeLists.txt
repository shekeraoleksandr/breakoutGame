set(SOURCE_FILES
        ball.cpp
        breakout.cpp
        brick.cpp
        paddle.cpp
        main.cpp
        )

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/breakout.h
        )

set(QRC_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/res/breakout.qrc
        )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(breakoutSrc
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${QRC_SOURCE_FILES}
        )

target_link_libraries(breakoutSrc
        PRIVATE
        BreakoutLib
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )

#if (WIN32)
#    target_link_options(breakoutSrc PRIVATE "/entry:mainCRTStartup")
#endif()
#
#if (APPLE)
#    # Since there appear to exist problems with NOT setting the RPATH when building
#    # by enabling CMAKE_KEEP_RPATH and others, we just set the libs absolute paths
#    # to the conan lib dir.
#
#    function(ChangeRPath target file new)
#        add_custom_command(TARGET breakoutSrc
#                POST_BUILD COMMAND
#                ${CMAKE_INSTALL_NAME_TOOL} -change @rpath/${file} ${new}/${file}
#                $<TARGET_FILE:breakoutSrc>)
#    endfunction()
#
#    foreach(qt_lib IN LISTS CONAN_LIBS_QT)
#        ChangeRPath(breakoutSrc lib${qt_lib}.dylib ${CONAN_LIB_DIRS_QT})
#    endforeach()
#endif ()
