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
		this->insertNewFood();
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
	if (checkSelfCollision() || checkWallCollision()) {
		gameState = GameState::GAMEOVER;
	}
}

bool Game::checkSelfCollision() {
	const auto& snakeBody = snake.getSnakeBody();
	auto headPositionIt = snakeBody.rend() - 1; // head have to be excluded from find as we look if head is equal to any other point

	auto it = std::find(snakeBody.rbegin(), headPositionIt, snakeBody.front());

	return !(it == headPositionIt);
}

bool Game::checkWallCollision() {
	return !boardSize.isInside(snake.getSnakeBody().front());
}

bool Game::checkIfAteFood() {
	const auto& snakeHead = snake.getSnakeBody().front();

	for (auto it = food.begin(); it != food.end(); ++it) {
		if (*it == snakeHead) {
			food.erase(it);
			this->insertNewFood();
			return true;
		}
	}

	return false;
}

void Game::insertNewFood() {
	while (true) {
		// [iterator, inserted]
		const auto result = food.insert({xDistribution(randomGenerator),
		                                 yDistribution(randomGenerator)});

		if (result.second) return;
	}
}
