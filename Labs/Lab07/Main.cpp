// Luke Underwood
// 3/24/20
// CS202
// Lab07
// Main.cpp

#include "Enemy.h"
#include <iostream>

int main()
{
	const Enemy enemy1;
	std::cout << enemy1;

	const Enemy enemy2("Goblin", 15, 5);
	std::cout << enemy2;

	Enemy enemy3;
	enemy3 = enemy2;
	std::cout << enemy3;
	return 0;
}