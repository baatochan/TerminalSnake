//
// Created by a19stude on 4/17/19.
//

#ifndef TERMINALSNAKE_USERINTERFACE_HPP
#define TERMINALSNAKE_USERINTERFACE_HPP

#include <utility>
#include <deque>
#include "Point.hpp"

class UserInterfaceI {
public:
	virtual std::pair<unsigned int, unsigned int> initialize() = 0;

	virtual void clear() = 0;

	virtual void drawDeque(const std::deque<Point>& object) = 0;

	virtual void drawPoint(Point object) = 0;

	virtual void refresh() = 0;

	virtual void printGameOver() = 0;

	virtual char getInput() = 0;
};

class UserInterface : public UserInterfaceI {
public:
	std::pair<unsigned int, unsigned int> initialize() override;

	void clear() override;

	void drawDeque(const std::deque<Point>& object) override;

	void drawPoint(Point object) override;

	void refresh() override;

	void printGameOver() override;

	char getInput() override;

};


#endif //TERMINALSNAKE_USERINTERFACE_HPP
