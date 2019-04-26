//
// Created by a19stude on 4/17/19.
//

#ifndef TERMINALSNAKE_USERINTERFACE_HPP
#define TERMINALSNAKE_USERINTERFACE_HPP

#include <utility>
#include <deque>
#include "Point.hpp"
#include "Enums.hpp"
#include "Dimension.hpp"

class UserInterfaceI {
public:
	virtual Dimension initialize() = 0;

	virtual void clear() = 0;

	virtual void drawDeque(const std::deque<Point>& object, char symbol) = 0;

	virtual void drawPoint(Point object, char symbol) = 0;

	virtual void refresh() = 0;

	virtual void printGameOver(const std::string& customMsg) = 0;

	virtual Direction getInput() = 0;
};

class UserInterface : public UserInterfaceI {
public:
	UserInterface();

	Dimension initialize() override;

	void clear() override;

	void drawDeque(const std::deque<Point>& object, char symbol) override;

	void drawPoint(Point object, char symbol) override;

	void refresh() override;

	void printGameOver(const std::string& customMsg) override;

	Direction getInput() override;

	Dimension windowSize;

};


#endif //TERMINALSNAKE_USERINTERFACE_HPP
