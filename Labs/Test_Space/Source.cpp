

#include<iostream>
#include<iomanip>
struct Value
{

};

int main()
{

	std::shared_ptr<Value> myValue;
	std::cout << myValue << " " << std::hex << myValue;

}