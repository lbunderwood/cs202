// Luke Underwood
// 1/28/2020
// cs202
// Lists_with_pointers
// ListMain.cpp

#include<iostream>
#include<list>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

unsigned int Factorial(unsigned int number) {
	return number <= 1 ? number : Factorial(number - 1) * number;
}
// wat
TEST_CASE("Factorials are computed", "[factorial]") {
	REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);
}
