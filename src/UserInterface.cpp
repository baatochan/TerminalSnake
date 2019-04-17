//
// Created by a19stude on 4/17/19.
//

#include <ncurses.h>
#include <stdexcept>
#include <chrono>
#include <thread>
#include "UserInterface.hpp"

std::pair<unsigned int, unsigned int> UserInterface::initialize() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE); // make keys work
	curs_set(0); // hide cursor
	timeout(100);

	getmaxyx(stdscr, windowSize.second, windowSize.first);

	return windowSize;
}

void UserInterface::clear() {
	::clear();
}

void UserInterface::drawDeque(const std::deque<Point>& object, const chtype symbol) {
	for (const auto& el : object) {
		mvaddch(el.y, el.x, symbol);
	}
}

void UserInterface::drawPoint(Point object, const chtype symbol) {
	mvaddch(object.y, object.x, symbol);
}

void UserInterface::refresh() {
	::refresh();
}

void UserInterface::printGameOver() {
	std::string gameOver = "Game Over!";
	attron(A_BOLD);
	mvprintw(windowSize.second/2, (windowSize.first - gameOver.size())/2, gameOver.data());
	echo();
	refresh();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	endwin();
}

Direction UserInterface::getInput(Direction previous) {
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
			return previous;
	}
}
