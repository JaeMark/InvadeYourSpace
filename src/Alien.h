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
	bool isAlienAlive;
public:
	Alien(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{ type } {
		collision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), 10, 10 };
		isAlienAlive = true;
	}


	void draw() const {
		switch(myType) {
		case Type::bottom:
			ofSetColor(255, 0, 0);
			ofDrawCircle(myCoordinate.x, myCoordinate.y, 10);
			break;
		case Type::middle:
			ofSetColor(0, 255, 0);
			ofDrawCircle(myCoordinate.x, myCoordinate.y, 10);
			break;
		case Type::top:
			ofSetColor(0, 0, 255);
			ofDrawCircle(myCoordinate.x, myCoordinate.y, 10);
			break;
		}
	}

	int value() const {
		int alienValue = 0;
		switch (myType) {
		case Type::bottom:
			alienValue = 10;
			break;
		case Type::middle:
			alienValue = 20;
			break;
		case Type::top:
			alienValue = 30;
			break;
		}
		return alienValue;
	}

	void update(Coordinate changeInCoordinate) {
		myCoordinate.x += changeInCoordinate.x;
		myCoordinate.y += changeInCoordinate.y;
		if (isAlienAlive) {
			collision.setX(myCoordinate.x);
			collision.setY(myCoordinate.y);
		} else {
			collision.setX(-1);
			collision.setY(-1);
		}

	}

	bool isOnBoundary(double leftBoundary, double rightBoundary) const {
		return (myCoordinate.x <= (leftBoundary + 5) || myCoordinate.x >= (rightBoundary - 5)) && isAlienAlive;
	}

	void destroy() {
		isAlienAlive = false;
	}

	bool isAlive() const {
		return isAlienAlive;
	}
};
