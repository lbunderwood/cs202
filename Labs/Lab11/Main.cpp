#include <iostream>
#include <string>

class Bean
{
public:
	Bean()
	{
		std::cout << "Bean::Bean()\t\t\t\t\tWith " << beans_ << " Beans" << std::endl;
	}

	Bean(int beanCount) : beans_(beanCount)
	{
		std::cout << "Bean::Bean(int beanCount)\t\t\tWith " << beans_ << " Beans" << std::endl;
	}

	~Bean()
	{
		std::cout << "Bean::~Bean()\t\t\t\t\tWith " << beans_ << " Beans" << std::endl;
	}

private:
	int beans_{ 100 };
};

class Type : Bean
{
public:
	Type() : Bean(75), name_("Pinto Bean")
	{
		std::cout << "Type::Type()\t\t\t\t\t" << name_ << std::endl;
	}

	Type(int beanCount, std::string typeName) : Bean(beanCount), name_(typeName)
	{
		std::cout << "Type::Type(int beanCount, std::string typeName)\t" << name_ << std::endl;
	}

	Type(int beanCount) : Bean(beanCount)
	{
		std::cout << "Type::Type()\t\t\t\t\t" << name_ << std::endl;
	}

	~Type()
	{
		std::cout << "Type::~Type()\t\t\t\t\t" << name_ << std::endl;
	}

private:
	std::string name_;
};

int main()
{
	{ Bean b; }
	std::cout << std::endl;
	{ Bean b(10000); }
	std::cout << std::endl;

	{ Type p; }
	std::cout << std::endl;
	{ Type l(10, "Lima Bean"); }
	std::cout << std::endl;
	{ Type u(666); }
	return 0;
}