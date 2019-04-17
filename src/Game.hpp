//
// Created by a19stude on 4/17/19.
//

#ifndef TERMINALSNAKE_GAME_HPP
#define TERMINALSNAKE_GAME_HPP


#include <memory>
#include <vector>
#include <random>
#include "Snake.hpp"
#include "UserInterface.hpp"
#include "Point.hpp"

class Game {
public:
	explicit Game(std::unique_ptr<UserInterfaceI> UI);

	void start();

private:
	void mainLoop();

	void gameOver();

	void checkIfMoveValid();

	bool checkSelfColision();

	bool checkWallColision(const Point& move);

	bool checkIfAteFood();

	Point generateRandomPoint();

	GameState gameState;

	std::unique_ptr<UserInterfaceI> UI;

	std::pair<unsigned int, unsigned int> windowSize;

	Snake snake;

	std::vector<Point> food;

	std::random_device seed;
	std::mt19937 randomGenerator;
	std::uniform_int_distribution<> xDistribution;
	std::uniform_int_distribution<> yDistribution;
};


#endif //TERMINALSNAKE_GAME_HPP
