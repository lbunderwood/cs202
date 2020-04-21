// Luke Underwood
// 4/20/2020
// cs202
// SVG Output 1
// Iditarod #5
// SvgCreator.h
// SvgCreator class header

#ifndef SVGCREATOR_H
#define SVGCREATOR_H


#include "CityList.h"
#include "CityPath.h"
#include <fstream>
#include <string>
#include <vector>

class SvgCreator
{
public:

	SvgCreator(std::string file);

	void drawCities(std::ofstream& ofs, const CityList& list);

	void drawPath(std::ofstream& ofs, const CityList& list, const CityPath& path);

	void draw(const std::string& filename, const CityList& list, const CityPath& path, double time);

private:

	std::string tspFilename_;

	int headerHeight_;
	int height_;
	int width_;
	int borderWidth_;
	int scale_;

};

#endif