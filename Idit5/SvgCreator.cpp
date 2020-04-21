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

void SvgCreator::drawCities(std::ofstream& ofs)
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

void SvgCreator::drawPath(std::ofstream& ofs)
{
	auto cityList = solver_.getCities();
	auto cityVec = cityList.getList();

	ofs << "<polyline points=\"";

	for (auto n : cityVec)
	{
		ofs << n.getCoords.first + borderWidth_ << ", "
			<< n.getCoords.second + headerHeight_ + borderWidth_ << " ";
	}

	ofs << "\"/>" << std::endl;
}


void SvgCreator::draw(const std::string& filename, int pathNum)
{
	std::ofstream ofs(filename);

	ofs << "<svg version=\"1.1\" baseProfile = \"full\" \n"
		"width = \"300\" height = \"200\" \n"
		"xmlns = \"http://www.w3.org/2000/svg\">";

	drawCities(ofs);
	drawPath(ofs);

	ofs << "</svg>";
}