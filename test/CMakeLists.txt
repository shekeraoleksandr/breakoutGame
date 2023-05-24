include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(breakout_test tests.cpp)

target_link_libraries(breakout_test
        PRIVATE
        GTest::GTest
        breakout_test_example
        )

add_test(breakout_test breakout_test)