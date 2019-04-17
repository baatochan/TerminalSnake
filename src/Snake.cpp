//
// Created by a19stude on 4/17/19.
//

#include "Snake.hpp"

Snake::Snake(Point startingPoint, Direction startingDirection) : currentDirection(startingDirection) {
	snakeBody.push_back(startingPoint);
	startingPoint.x--;
	snakeBody.push_back(startingPoint);
	startingPoint.x--;
	snakeBody.push_back(startingPoint);
}

void Snake::makeAMove() {
	snakeBody.pop_back();

	Point head = snakeBody.front();

	switch (currentDirection) {

		case Direction::UP:
			head.y--;
			break;

		case Direction::RIGHT:
			head.x++;
			break;

		case Direction::DOWN:
			head.y--;
			break;

		case Direction::LEFT:
			head.x--;
			break;

	}

	snakeBody.push_front(head);
}

bool Snake::setDirection(Direction newDirection) {
	switch (newDirection) {

		case Direction::UP:
			if (currentDirection == Direction::UP || currentDirection == Direction::DOWN) {
				return false;
			} else {
				currentDirection = newDirection;
				return true;
			}

		case Direction::RIGHT:
			if (currentDirection == Direction::RIGHT || currentDirection == Direction::LEFT) {
				return false;
			} else {
				currentDirection = newDirection;
				return true;
			}

		case Direction::DOWN:
			if (currentDirection == Direction::DOWN || currentDirection == Direction::UP) {
				return false;
			} else {
				currentDirection = newDirection;
				return true;
			}

		case Direction::LEFT:
			if (currentDirection == Direction::LEFT || currentDirection == Direction::RIGHT) {
				return false;
			} else {
				currentDirection = newDirection;
				return true;
			}

	}
}

const std::deque<Point>& Snake::getSnakeBody() const {
	return snakeBody;
}
