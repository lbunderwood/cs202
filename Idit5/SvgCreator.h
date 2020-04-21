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

class SvgCreator
{
public:

	SvgCreator();

private:

	TspSolver solver_;

	int height_;
	int width_;

};

#endif