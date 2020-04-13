// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 1
// Iditarod #3
// CityNode.cpp
// CityNode class implementation

#include "CityNode.h"

#include<iostream>

CityNode::CityNode() 
	: nodeNum_( 0 ), latitude_( 0 ), longitude_( 0 ), graphX_( 0 ), graphY_( 0 )
{
	std::cout << "ERROR BAD NODE";
}

CityNode::CityNode(int num, double latitude, double longitude)
	: nodeNum_( num ), latitude_(latitude), longitude_(longitude), graphX_(0), graphY_(0) {}

CityNode::~CityNode() {}

std::pair<double, double> CityNode::getCoords() const
{
	return std::pair<double, double>(latitude_, longitude_);
}