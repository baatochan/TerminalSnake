//
// Created by a19stude on 4/17/19.
//

#include <algorithm>
#include "Game.hpp"

Game::Game(std::unique_ptr<UserInterfaceI> UI)
             : gameState(GameState::NOTSTARTED)
             , UI(std::move(UI))
             , windowSize(this->UI->initialize())
             , snake({static_cast<int>(windowSize.first/2)
					, static_cast<int>(windowSize.second/2)}
					, Direction::RIGHT)
			 , seed()
			 , randomGenerator(seed())
			 , xDistribution(0, windowSize.first)
			 , yDistribution(0, windowSize.second) {
	for (int i = 0; i < 3; ++i) {
		food.push_back(this->generateRandomPoint());
	}
}

void Game::start() {
	this->mainLoop();
	this->gameOver();
}

void Game::mainLoop() {
	gameState = GameState::INPROGRESS;
	Direction dir = Direction::RIGHT; // have to be as the one passed in snake constructor
	bool shouldGrow = false;
	while (true) {
		UI->clear();

		UI->drawDeque(snake.getSnakeBody(), '#');
		for (const auto& el : food) {
			UI->drawPoint(el, 'X');
		}

		UI->refresh();

		dir = UI->getInput(dir);
		snake.setDirection(dir);

		if (shouldGrow) {
			snake.grow();
		} else {
			snake.makeAMove();
		}

		checkIfMoveValid();

		shouldGrow = checkIfAteFood();

		if (gameState == GameState::GAMEOVER) {
			break;
		}
	}
}

void Game::gameOver() {
	UI->printGameOver();
}

void Game::checkIfMoveValid() {
	if (checkSelfColision() || checkWallColision(snake.getSnakeBody().front())) {
		gameState = GameState::GAMEOVER;
	}
}

bool Game::checkSelfColision() {
	const auto& snakeBody = snake.getSnakeBody();
	auto it = std::find_if(snakeBody.rbegin(), snakeBody.rend() - 1, [&](const auto& val){ return val == snakeBody.front(); });

	if (it == snakeBody.rend() - 1) {
		return false;
	} else {
		return true;
	}
}

bool Game::checkWallColision(const Point& move) {
	return move.x < 0 || move.x >= static_cast<int>(windowSize.first) || move.y < 0 || move.y >= static_cast<int>(windowSize.second);
}

bool Game::checkIfAteFood() {
	const auto& snakeHead = snake.getSnakeBody().front();

	for (auto it = food.begin(); it < food.end(); ++it) {
		if (*it == snakeHead) {
			food.erase(it);
			food.push_back(generateRandomPoint());
			return true;
		}
	}

	return false;
}

Point Game::generateRandomPoint() {
	// check for occupied points

	return {xDistribution(randomGenerator), yDistribution(randomGenerator)};
}
