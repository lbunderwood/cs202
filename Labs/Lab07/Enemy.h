// Luke Underwood
// 3/24/20
// CS202
// Lab07
// Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

#include<string>
#include<utility>

class Enemy
{
public:
	Enemy();

	std::string getName() const;

	std::pair<double, double> getStats() const;

private:
	std::string name_;
	double health_;
	double attack_;
};

std::ostream& operator<<(std::ostream& os, const Enemy& enemy);

#endif