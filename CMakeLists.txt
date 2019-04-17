cmake_minimum_required(VERSION 3.13)
project(TerminalSnake)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES )
file(GLOB TEST_SOURCES )

add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(tests)
