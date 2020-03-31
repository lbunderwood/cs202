#ifndef CART_H
#define CART_H

#include<iostream>
#include<iomanip>

class Cart
{
public:
	Cart() : fruitQty_{ 0 }, meatQty_{ 0 } {}

	static void setPrices(double fruit, double meat)
	{
		fruitPrice_ = fruit;
		meatPrice_ = meat;
	}

	void addFruit()
	{
		fruitQty_++;
	}
	void addMeat()
	{
		meatQty_++;
	}

	void printCost()
	{
		static int count = 0;
		count++;
		std::cout << "Time " << count << " checking cost : $"
			<< std::fixed << std::setprecision(2) 
			<< (double)fruitQty_ * fruitPrice_ + (double)meatQty_ * meatPrice_
			<< std::endl;
	}

private:
	static double fruitPrice_;
	static double meatPrice_;

	int fruitQty_;
	int meatQty_;
};

double Cart::fruitPrice_ = 2.49;
double Cart::meatPrice_ = 5.99;

#endif