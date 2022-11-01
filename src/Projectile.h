#pragma once
#include "Coordinate.h"

class Projectile {
	enum class Type { friendly, enemy };

	Coordinate myCoordinate;
	Type myType;
public:
	Projectile(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{type} {}
};
