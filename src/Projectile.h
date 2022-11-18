#pragma once
#include "Coordinate.h"
#include "ofGraphics.h"
#include "ofImage.h"

class Projectile {
public:
	enum class Type { friendly, enemy };
private:
	ofImage myAvatar;
	Coordinate myCoordinate;
	int mySpeed;
	Type myType;
public:
	ofRectangle collision;
	
	Projectile(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{type} {
		if (myType == Type::friendly) {
			myAvatar.load("Assets/playerProjectile.png");
			mySpeed = -5;
			myAvatar.rotate90(3);
		}
		else if (myType == Type::enemy) {
			myAvatar.load("Assets/enemyProjectile.png");
			mySpeed = 2;
			myAvatar.rotate90(1);
		}
		myAvatar.resize(20, 40);
		collision = ofRectangle{static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), myAvatar.getWidth(), myAvatar.getHeight() };
	}

	void draw() {
		ofSetColor(255);
		update();
		myAvatar.draw(myCoordinate.x, myCoordinate.y);
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
