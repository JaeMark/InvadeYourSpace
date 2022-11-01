#pragma once
#include "Coordinate.h"

class Alien {
	enum class Type{ bottom, middle, top };

	Coordinate myCoordinate;
	Type myType;
public:
	Alien(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{ type } {}
};
