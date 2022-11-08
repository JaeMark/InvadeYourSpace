#pragma once
#include "Coordinate.h"
#include "ofGraphics.h"

class Alien {
public:
	enum class Type{ bottom, middle, top };
	ofRectangle collision;
private:
	Coordinate myCoordinate;
	Type myType;
public:
	Alien(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{ type } {
		collision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), 10, 10 };
	}


	void draw() {
		switch(myType) {
		case Type::bottom:
			ofSetColor(255, 0, 0);
			ofDrawCircle(myCoordinate.x, myCoordinate.y, 10);
		case Type::middle:
			ofSetColor(0, 255, 0);
			ofDrawCircle(myCoordinate.x, myCoordinate.y, 10);
		case Type::top:
			ofSetColor(0, 0, 255);
			ofDrawCircle(myCoordinate.x, myCoordinate.y, 10);
		}
	}

	void update(Coordinate newCoordinate) {
		myCoordinate.x = newCoordinate.x;
		myCoordinate.y = newCoordinate.y;
		collision.setX(myCoordinate.x);
		collision.setY(myCoordinate.y);
	}
};
