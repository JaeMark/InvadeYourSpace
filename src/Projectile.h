#pragma once
#include "Coordinate.h"
#include "ofGraphics.h"

class Projectile {
public:
	enum class Type { friendly, enemy };
private:
	Coordinate myCoordinate;
	int mySpeed;
	Type myType;
public:
	Projectile(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{type} {
		if (myType == Type::friendly) { mySpeed = 15; }
		else if (myType == Type::enemy) { mySpeed = 1; }
	}

	void draw() {
		ofSetColor(255);
		myCoordinate.y -= mySpeed;
		ofDrawCircle(myCoordinate.x, myCoordinate.y, 5);
	}
};
