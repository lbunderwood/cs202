#include<iostream>

class Animal
{
public:
	virtual void makeNoise()
	{
		std::cout << "An animal (base class) is making noise (virtual function)\n\n";
	}

	void eat()
	{
		std::cout << "An amimal (base class) is eating (non-virtual function)\n\n";
	}
};

class Dog : public Animal
{
public:
	void makeNoise() override
	{
		std::cout << "A dog (derived class) is barking (override)\n\n";
	}

	void eat()
	{
		std::cout << "A dog (derived class) is eating\n\n";
	}
};

int main()
{
	Animal a;
	Dog d;

	Animal* animalToAnimal = &a;
	Animal* animalToDog = &d;
	Dog* dogToDog = &d;

	std::cout << "An animal is about to eat (Calling non-virtual function from base class pointer to base)\n";
	animalToAnimal->eat();

	std::cout << "An animal is about to make noise (Calling virtual function from base class pointer to base)\n";
	animalToAnimal->makeNoise();

	std::cout << "---------------------------------------\n";
	
	std::cout << "An animal is about to eat (Calling non-virtual function from base class pointer to derived class)\n";
	animalToDog->eat();

	std::cout << "A dog is about to bark (Calling virtual function from base class pointer to derived class)\n";
	animalToDog->makeNoise();
	
	std::cout << "---------------------------------------\n";

	std::cout << "An dog is about to eat (Calling non-virtual function from derived class pointer to derived class)\n";
	dogToDog->eat();

	std::cout << "An dog is about to bark (Calling virtual function from derived class pointer to derived class)\n";
	dogToDog->makeNoise();

	std::cout << "IN CONCLUSION, THE FIRST TIME A DOG BARKS DEMONSTRATES POLYMORPHISM, SINCE A FUNCTION IS BEING OVERRIDDEN\n";
}