// Luke Underwood
// 3/24/20
// CS202
// Lab07
// Enemy.cpp

#include"Enemy.h"
#include<iostream>
Enemy::Enemy() 
	: name_{ "Orc" }, health_{ 100.0 }, attack_{ 30.0 } {}

Enemy::Enemy(std::string name, double health, double attack)
	: name_{ name }, health_{ health }, attack_{ attack } {}

std::string Enemy::getName() const
{
	return name_;
}

std::pair<double, double> Enemy::getStats() const
{
	return { health_, attack_ };
}

Enemy& Enemy::operator=(const Enemy& old)
{
	name_ = old.getName();
	health_ = old.getStats().first;
	attack_ = old.getStats().second;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy)
{
	os << enemy.getName() << ": Health = " << enemy.getStats().first 
		<< ", Attack = " << enemy.getStats().second << std::endl;
	return os;
}