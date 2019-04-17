//
// Created by a19stude on 4/17/19.
//

#ifndef TERMINALSNAKE_SNAKE_HPP
#define TERMINALSNAKE_SNAKE_HPP


#include <deque>
#include "Point.hpp"
#include "Enums.hpp"

class Snake {
public:
	Snake(Point startingPoint, Direction startingDirection);

	void makeAMove();

	void grow();

	bool setDirection(Direction newDirection);

	const std::deque<Point>& getSnakeBody() const;

private:
	std::deque<Point> snakeBody;

	Direction currentDirection;

};


#endif //TERMINALSNAKE_SNAKE_HPP
