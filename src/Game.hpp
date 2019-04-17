//
// Created by a19stude on 4/17/19.
//

#ifndef TERMINALSNAKE_GAME_HPP
#define TERMINALSNAKE_GAME_HPP


#include <memory>
#include <vector>
#include "Snake.hpp"
#include "UserInterface.hpp"
#include "Point.hpp"

class Game {
public:
	Game();

	void start();

private:
	void mainLoop();

	void gameOver();

	bool checkIfNextMoveValid();

	bool checkSelfColision(Point move);

	bool checkWallColision(Point move);

	Snake snake;

	std::vector<Point> food;

	std::unique_ptr<UserInterfaceI> UI;

	std::pair<unsigned int, unsigned int> borderSize;
};


#endif //TERMINALSNAKE_GAME_HPP
