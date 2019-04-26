//
// Created by a19stude on 4/17/19.
//

#include <algorithm>
#include "Game.hpp"

Game::Game(std::unique_ptr<UserInterfaceI> UI)
             : gameState(GameState::NOTSTARTED)
             , UI(std::move(UI))
             , windowSize(this->UI->initialize())
             , snake({static_cast<int>(windowSize.first / 2)
					, static_cast<int>(windowSize.second / 2)}
					, Direction::NOTSPECIFIED)
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
	bool shouldGrow = false;
	while (true) {
		UI->clear();

		UI->drawDeque(snake.getSnakeBody(), '#');
		for (const auto& el : food) {
			UI->drawPoint(el, 'X');
		}

		UI->refresh();

		Direction dir = UI->getInput();
		if (dir != Direction::NOTSPECIFIED)
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
	std::string msg = "Snake size: " + std::to_string(snake.getSnakeBody().size());
	UI->printGameOver(msg);
}

void Game::checkIfMoveValid() {
	if (checkSelfCollision() || checkWallCollision(snake.getSnakeBody().front())) {
		gameState = GameState::GAMEOVER;
	}
}

bool Game::checkSelfCollision() {
	const auto& snakeBody = snake.getSnakeBody();
	auto headPositionIt = snakeBody.rend() - 1;

	auto it = std::find_if(snakeBody.rbegin(), headPositionIt,
	                       [&](const auto& val) { return val == snakeBody.front(); });

	return !(it == headPositionIt);
}

bool Game::checkWallCollision(const Point& move) {
	return move.x < 0 || move.x >= static_cast<int>(windowSize.first) ||
	       move.y < 0 || move.y >= static_cast<int>(windowSize.second);
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
	bool newPositionValid;
	do {
		Point newFood = {xDistribution(randomGenerator), yDistribution(randomGenerator)};

		auto it = std::find_if(food.begin(), food.end(), [&](const auto& val) { return val == newFood; });
		newPositionValid = it == food.end(); // newPositionValid if different than all other food
	} while (!newPositionValid);

	return {xDistribution(randomGenerator), yDistribution(randomGenerator)};
}
