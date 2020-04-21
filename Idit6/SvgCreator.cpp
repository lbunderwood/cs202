// Luke Underwood
// 4/20/2020
// cs202
// SVG Output 1
// Iditarod #5
// SvgCreator.cpp
// SvgCreator class implementation

#include "SvgCreator.h"
#include <fstream>
#include <iostream>

SvgCreator::SvgCreator(std::string file) : 
	headerHeight_{ 100 }, height_{ 1500 + headerHeight_ }, 
	width_{ 2000 }, borderWidth_{ 50 }, scale_{10}, tspFilename_{ file } {}

void SvgCreator::drawCities(std::ofstream& ofs, const CityList& list)
{
	auto cityVec = list.getList();

	int citySize = 10;

	for (auto n : cityVec)
	{
		ofs << "<circle cx=\"" << n.getCoords().first / scale_ + borderWidth_
			<< "\" cy=\"" << n.getCoords().second / scale_ + headerHeight_ 
			+ borderWidth_
			<< "\" r=\"" << citySize << "\" fill=\"red\"/>" << std::endl;
	}
}

void SvgCreator::drawPath(std::ofstream& ofs, int pathNum)
{
	auto cityList = solver_.getCities();
	auto cityVec = cityList.getList();
	auto paths = solver_.getPaths();


	ofs << "<polyline points=\"";

	for (auto n : paths[pathNum].getPath())
	{
		ofs << cityVec[n].getCoords().first / scale_ + borderWidth_ 
			<< ", "
			<< cityVec[n].getCoords().second / scale_ + headerHeight_ 
			+ borderWidth_ << " ";
	}

	ofs << "\" stroke=\"blue\" fill=\"transparent\" stroke-width=\"5\"/>" 
		<< std::endl;
}


void SvgCreator::draw(const std::string& filename, int pathNum)
{
	std::ofstream ofs(filename);

	ofs << "<svg version=\"1.1\" baseProfile = \"full\" \n"
		"width = \"" << width_ << "\" height = \"" << height_ << "\" \n"
		"xmlns = \"http://www.w3.org/2000/svg\">" << std::endl;

	auto paths = solver_.getPaths();
	auto cities = solver_.getCities();
	auto times = solver_.getTimes();
	auto distances = solver_.getDistances();

	ofs << "<rect x=\"0\" y=\"0\" width=\"" << width_ << "\" height=\""
		<< headerHeight_ << "\" fill=\"blue\"/>" << std::endl
		<< "<text x=\"50\" y=\"70\" font-size=\"80\" fill=\"white\">"
		<< filename << "</text>" << std::endl
		<< "<text x=\"750\" y=\"70\" font-size=\"80\" fill=\"white\">"
		<< tspFilename_ << "</text>" << std::endl
		<< "<text x=\"1300\" y=\"70\" font-size=\"80\" fill=\"white\">"
		<< solver_.getCities().size() << " - city problem </text>"
		<< std::endl
		<< "<text x=\"50\" y=\"1570\" font-size=\"80\">"
		<< "Distance = " << distances[pathNum] << "</text>" 
		<< std::endl
		<< "<text x=\"1000\" y=\"1570\" font-size=\"80\">"
		<< "Time Elapsed = " << times[pathNum] << "</text>"
		<< std::endl;

	drawPath(ofs, pathNum);
	drawCities(ofs);

	ofs << "</svg>";
}

void SvgCreator::run()
{
	solver_.readFile(tspFilename_);
	solver_.solve();

	draw("random.svg", 0);
	draw("greedy.svg", 1);
	draw("customAlg.svg", 2);
	std::cout << "File Creation Complete!" << std::endl;
}