// Luke Underwood
// 3/24/20
// CS202
// Lab07
// Enemy.cpp

#include"Enemy.h"
#include<iostream>
Enemy::Enemy() 
	: name_{ "Orc" }, health_{ 100.0 }, attack_{ 30.0 } {}

std::string Enemy::getName() const
{
	return name_;
}

std::pair<double, double> Enemy::getStats() const
{
	return { health_, attack_ };
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy)
{
	std::cout << enemy.getName() << ": Health = " << enemy.getStats().first 
		<< ", Attack = " << enemy.getStats().second << std::endl;
}