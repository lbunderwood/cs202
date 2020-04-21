// Luke Underwood
// 4/20/2020
// cs202
// SVG Output 1
// Iditarod #5
// SvgCreator.cpp
// SvgCreator class implementation

#include "SvgCreator.h"
#include <fstream>

SvgCreator::SvgCreator() : 
	headerHeight_{ 1000 }, height_{ 15000 + headerHeight_ }, 
	width_{ 20000 }, borderWidth_{ 100 } {}

void SvgCreator::drawCities(std::ofstream ofs)
{
	auto cityList = solver_.getCities();
	
	auto cityVec = cityList.getList();

	int citySize = 20;

	for (auto n : cityVec)
	{
		ofs << "<circle cx=\"" << n.getCoords.first + borderWidth_
			<< "\" cy=\"" << n.getCoords.second + headerHeight_ + borderWidth_
			<< "\" r=\"" << citySize << "\"/>" << std::endl;
	}

}