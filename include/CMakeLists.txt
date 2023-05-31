include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(HEADER_FILES
        ball.h
        breakout.h
        brick.h
        paddle.h
        )

add_library(BreakoutLib STATIC
        ${HEADER_FILES}
        )

target_link_libraries(BreakoutLib
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        coverage_config
)