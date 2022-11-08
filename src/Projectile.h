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
		if (myType == Type::friendly) { mySpeed = 15; }
		else if (myType == Type::enemy) { mySpeed = 1; }
		collision = ofRectangle{static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), 10, 10 };
	}

	void draw() {
		ofSetColor(255);
		update();
		ofDrawCircle(myCoordinate.x, myCoordinate.y, 5);
	}

	void update() {
		myCoordinate.y -= mySpeed;
		collision.setY(myCoordinate.y);
	}

	//CLEAN UP PROJECTILES
};
