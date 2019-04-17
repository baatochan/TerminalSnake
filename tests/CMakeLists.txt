find_package(Threads REQUIRED)
enable_testing()
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

add_executable(runAllTests ${TEST_SOURCES} ${SOURCES})

target_link_libraries(runAllTests gtest gmock gtest_main Threads::Threads)
add_test(AllTests runAllTests)
