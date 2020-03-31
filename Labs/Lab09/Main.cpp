#include"Cart.h"

int main()
{
	Cart cart1;
	for (int i = 0; i < 4; i++)
	{
		cart1.addFruit();
		cart1.addMeat();
	}
	cart1.printCost();


	Cart cart2;
	cart2.addFruit();
	cart2.printCost();


	Cart::setPrices(3.0, 7.0);


	cart1.printCost();
	cart2.printCost();
}