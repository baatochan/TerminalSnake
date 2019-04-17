cmake_minimum_required(VERSION 3.13)
project(TerminalSnake)

set(CMAKE_CXX_STANDARD 17)

add_definitions(
		-Wall
		-Wextra
		-Wpedantic
		-Wfatal-errors
)

add_subdirectory(googletest)

set(CURSES_USE_NCURSES TRUE)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)
enable_testing()
include_directories(${CURSES_INCLUDE_DIRS})
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

set(SOURCE_FILES src/Game.cpp src/Game.hpp src/Snake.cpp src/Snake.hpp src/UserInterface.cpp src/UserInterface.hpp src/Point.cpp src/Point.hpp)
set(TESTS_SOURCE_FILES tests/SnakeTest.cpp tests/PointTest.cpp)

add_executable(TerminalSnake src/main.cpp ${SOURCE_FILES} src/Enums.hpp)
add_executable(runAllTests ${TESTS_SOURCE_FILES} ${SOURCE_FILES})

target_link_libraries(TerminalSnake ${CURSES_LIBRARIES})
target_link_libraries(runAllTests gtest gmock gtest_main Threads::Threads ${CURSES_LIBRARIES})
add_test(AllTests runAllTests)
