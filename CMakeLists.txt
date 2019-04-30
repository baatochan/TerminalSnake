cmake_minimum_required(VERSION 3.2)
project(TerminalSnake)

### Set default build type ###
if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
	if (NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
	endif()
endif()

### Basic settings ###
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/Enums.hpp src/Game.cpp src/Game.hpp src/Snake.cpp src/Snake.hpp src/UserInterface.cpp src/UserInterface.hpp src/Point.cpp src/Point.hpp src/Dimension.cpp src/Dimension.hpp)

### Basic target - Terminal Snake ###
set(CURSES_USE_NCURSES TRUE)
find_package(Curses) # not using REQUIRED for custom error message
if (NOT ${CURSES_FOUND})
	message(FATAL_ERROR "Could not find Curses.\nYou can install it using \"sudo apt-get install libncurses5-dev\".")
endif()
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(TerminalSnake src/main.cpp ${SOURCE_FILES})

target_link_libraries(TerminalSnake ${CURSES_LIBRARIES})

### Run target ###
add_custom_target(run
        COMMAND TerminalSnake
        DEPENDS TerminalSnake
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

if (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
	### Basic settings for Debug ###
	add_definitions(
	        -Wall
	        -Wextra
	        -Wpedantic
	        -Wfatal-errors
	)

	set(TESTS_SOURCE_FILES tests/SnakeTest.cpp tests/PointTest.cpp tests/DimensionTest.cpp)

	### Unit test target (only for Debug and RelWithDebInfo) ###
	find_package(Threads REQUIRED)

	option(INSTALL_GMOCK "Install Googletest's GMock?" OFF)
	option(INSTALL_GTEST "Install Googletest's GTest?" OFF)
	add_subdirectory(googletest)
	include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

	add_executable(UnitTests ${TESTS_SOURCE_FILES} ${SOURCE_FILES})

	target_link_libraries(UnitTests gtest gmock gtest_main Threads::Threads ${CURSES_LIBRARIES})

	enable_testing()
	add_test(AllTests UnitTests)

	### Run unit test target (only for Debug and RelWithDebInfo) ###
	add_custom_target(runUnitTests
	        COMMAND UnitTests
	        DEPENDS UnitTests
	        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
	)
endif()

### Install target ###
if (NOT DEFINED INSTALL_TERMINALSNAKE)
	set(INSTALL_TERMINALSNAKE ON)
endif()

if (INSTALL_TERMINALSNAKE MATCHES ON)
	install(TARGETS TerminalSnake
	        DESTINATION bin
	)
endif()
