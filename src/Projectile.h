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
	ofRectangle collision;
	
	Projectile(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{type} {
		if (myType == Type::friendly) { mySpeed = -5; }
		else if (myType == Type::enemy) { mySpeed = 2; }
		collision = ofRectangle{static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), 10, 10 };
	}

	void draw() {
		ofSetColor(255);
		update();
		ofDrawCircle(myCoordinate.x, myCoordinate.y, 5);
	}

	void update() {
		myCoordinate.y += mySpeed;
		collision.setY(myCoordinate.y);
	}

	void update(const Coordinate coord) {
		myCoordinate = coord;
		collision.setX(coord.x);
		collision.setY(coord.y);
	}

	//CLEAN UP PROJECTILES
};
