find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(TerminalSnake main.cpp ${SOURCES})

target_link_libraries(TerminalSnake ${CURSES_LIBRARIES})
