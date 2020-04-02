#include <iostream>

class TestObject
{
public:

	TestObject() { std::cout << "TestObject created" << std::endl; }
	~TestObject() { std::cout << "TestObject destroyed" << std::endl; }
};

void functionC()
{
	throw std::runtime_error("Runtime Error: functionC failure");
}

void functionB()
{
	TestObject TO;
	std::cout << "Starting functionB()\n";
	functionC();
	std::cout << "Ending functionB()\n";
}

void functionA()
{
	try
	{
		functionB();
		std::cout << "functionB worked, but should not have." << std::endl;
	}
	catch(std::exception& e)
	{
		std::cout << "Caught an exception: " << e.what() << std::endl;
	}
	std::cout << "functionB falied as intended." << std::endl;
}

int main()
{
	std::cout << "Starting main()" << std::endl;
	functionA();
	std::cout << "Ended normally." << std::endl;
	return 0;
}
