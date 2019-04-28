//
// Created by a19stude on 4/17/19.
//

#include <algorithm>
#include "Game.hpp"

Game::Game(std::unique_ptr<UserInterfaceI> UI)
             : gameState(GameState::NOTSTARTED)
             , UI(std::move(UI))
             , boardSize(this->UI->initialize())
             , snake({static_cast<int>(boardSize.height / 2)
					, static_cast<int>(boardSize.width / 2)}
					, Direction::NOTSPECIFIED)
			 , seed()
			 , randomGenerator(seed())
			 , xDistribution(0, boardSize.height - 1)
			 , yDistribution(0, boardSize.width - 1) {
	for (int i = 0; i < 3; ++i) {
		food.push_back(this->generateFoodPosition());
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
	return !boardSize.isInside(move);
}

bool Game::checkIfAteFood() {
	const auto& snakeHead = snake.getSnakeBody().front();

	for (auto it = food.begin(); it < food.end(); ++it) {
		if (*it == snakeHead) {
			food.erase(it);
			food.push_back(generateFoodPosition());
			return true;
		}
	}

	return false;
}

Point Game::generateFoodPosition() {
	bool newPositionValid;
	Point newFood{};

	do {
		newFood = {xDistribution(randomGenerator), yDistribution(randomGenerator)};

		auto it = std::find(food.begin(), food.end(), newFood);
		newPositionValid = it == food.end(); // newPositionValid if different than all other food
	} while (!newPositionValid);

	return newFood;
}
