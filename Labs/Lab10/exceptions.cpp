#include <iostream>

void functionC()
{
  //your code here
}

void functionB()
{
  //your code here
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
