//
// Created by a19stude on 4/17/19.
//

#include <ncurses.h>
#include <stdexcept>
#include <chrono>
#include <thread>
#include "UserInterface.hpp"

Dimension UserInterface::initialize() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE); // make keys work
	curs_set(0); // hide cursor
	timeout(100);

	getmaxyx(stdscr, windowSize.height, windowSize.width);

	return windowSize;
}

void UserInterface::clear() {
	::clear();
}

void UserInterface::drawDeque(const std::deque<Point>& object, const char symbol) {
	for (const auto& el : object) {
		mvaddch(el.y, el.x, symbol);
	}
}

void UserInterface::drawPoint(Point object, const char symbol) {
	mvaddch(object.y, object.x, symbol);
}

void UserInterface::refresh() {
	::refresh();
}

void UserInterface::printGameOver(const std::string& customMsg) {
	std::string gameOver = "Game Over!";
	attron(A_BOLD);
	mvprintw(windowSize.height / 2, (windowSize.width - static_cast<int>(gameOver.size())) / 2, gameOver.data());
	if (!customMsg.empty()) {
		mvprintw((windowSize.height / 2) + 1, (windowSize.width - static_cast<int>(customMsg.size())) / 2,
		         customMsg.data());
	}
	echo();
	refresh();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	endwin();
}

Direction UserInterface::getInput() {
	int ch = getch();
	switch (ch) {
		case KEY_LEFT:
			return Direction::LEFT;
		case KEY_RIGHT:
			return Direction::RIGHT;
		case KEY_DOWN:
			return Direction::DOWN;
		case KEY_UP:
			return Direction::UP;
		default:
			return Direction::NOTSPECIFIED;
	}
}

UserInterface::UserInterface() : windowSize({0, 0}) {}
