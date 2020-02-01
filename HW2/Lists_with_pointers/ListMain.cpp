// Luke Underwood
// 1/28/2020
// cs202
// Lists_with_pointers
// ListMain.cpp

#include<iostream>
#include<list>
#include<algorithm>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

struct Gods
{
	std::string hel = "hound";
	std::string frigga = "owl";
	std::string odin = "raven";
	std::string loki = "serpent";
	std::string thor = "sheep";
	std::string sif = "swans";
};

TEST_CASE("Fifo, Lifo, Instert, and Sort", "[Linked Lists]") {
	Gods gods;

	std::list<std::string> og = { gods.hel, gods.frigga, gods.odin, gods.thor };
	std::list<std::string> fifo = og;
	std::list<std::string> lifo = og;

	REQUIRE(og == fifo);
	REQUIRE(og == lifo);

	fifo.push_back(gods.sif);
	lifo.push_back(gods.sif);

	REQUIRE(fifo.back() == gods.sif);
	REQUIRE(lifo.back() == gods.sif);

	fifo.pop_front();
	lifo.pop_back();

	REQUIRE(fifo.front() == gods.frigga);
	REQUIRE(fifo.back() == gods.sif);
	REQUIRE(lifo == og);

	std::list<std::string>::iterator searchTargetBegin = og.begin();
	std::advance(searchTargetBegin, 2);
	std::list<std::string>::iterator searchTargetEnd = searchTargetBegin;
	searchTargetEnd++;
	std::list<std::string>::iterator searchResult = og.end();
	searchResult = std::search(og.begin(), og.end(), searchTargetBegin, searchTargetEnd);

	REQUIRE(searchResult == searchTargetBegin);

	og.insert(searchTargetEnd, gods.loki);
	searchTargetEnd--;

	REQUIRE(*searchTargetEnd == gods.loki);

	for (auto n : og)
	{
		std::cout << n << std::endl;
	}
}
