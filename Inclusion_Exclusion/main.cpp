#include <string>
#include <iostream>
#include "the_game.h"
#

int main() {
	std::cout << "Want to play a game??\n";
	std::cout << "[1] Yes\n";
	std::cout << "[2] No\n";
	std::cout << "[3] Quit\n";
	switch (std::cin.get())
	{
	case '1':
		std::cout << "Welcome to the Game!\n";
		the_game();
		break;
	case '2':
		std::cout << "A little late to leave don;t you think. We should play anyway.\n";
		the_game();
		break;
	case '3':
		std::cout << "See you soon!\n";
		break;
	default:
		std::cout << "Well thats not an answer.\n";
		break;
	}
	return 0;
}