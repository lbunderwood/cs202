// Luke Underwood
// 2/6/2020
// cs202
// Lab05
// Main.cpp

#include<fstream>
#include<iostream>

int main()
{
	std::fstream f;
	f.open("data.dat", std::ios::binary);
	while (f)
	{
		f.read();
	}
}