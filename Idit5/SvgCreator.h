// Luke Underwood
// 4/20/2020
// cs202
// SVG Output 1
// Iditarod #5
// SvgCreator.h
// SvgCreator class header

#ifndef SVGCREATOR_H
#define SVGCREATOR_H

#include "TspSolver.h"
#include <fstream>

class SvgCreator
{
public:

	SvgCreator();

	void drawCities(std::ofstream ofs);

private:

	TspSolver solver_;
	std::string tspFilename_;

	int headerHeight_;
	int height_;
	int width_;
	int borderWidth_;

};

#endif