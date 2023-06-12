include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(HEADER_FILES
        ball.h
        brick.h
        paddle.h
        )

add_library(BreakoutLib STATIC
        ${HEADER_FILES}
        )

set_target_properties(BreakoutLib PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(BreakoutLib
        Qt6::Core
        coverage_config
)