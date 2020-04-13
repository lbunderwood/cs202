// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 1
// Iditarod #3
// CityNode.h
// CityNode class header

#ifndef CITYNODE_H
#define CITYNODE_H

class CityNode
{
public:

	CityNode();
	CityNode(int num, double latitude, double longitude);
	~CityNode();

private:

	size_t nodeNum_;
	double latitude_;
	double longitude_;
	double graphX_;
	double graphY_;

};

#endif