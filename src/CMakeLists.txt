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

