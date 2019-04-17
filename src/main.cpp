#include "Game.hpp"

int main() {
	auto UI = std::unique_ptr<UserInterfaceI>(new UserInterface);
	Game game(std::move(UI));

	game.start();

	return 0;
}
