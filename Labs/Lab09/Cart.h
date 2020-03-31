#ifndef CART_H
#define CART_H

#include<iostream>
#include<iomanip>

class Cart
{
public:
	Cart() : fruitQty_{ 0 }, meatQty_{ 0 } 
	{
		fruitPrice_ = 2.49;
		meatPrice_ = 5.99;
	}

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
		static int count = 1;
		count++;
		std::cout << "Time " << count << " checking cost : $" 
			<< std::put_money(fruitQty_ * fruitPrice_ + meatQty_ * meatPrice_);
	}

private:
	static double fruitPrice_;
	static double meatPrice_;

	int fruitQty_;
	int meatQty_;
};

#endif