#pragma once
#include "Coordinate.h"
#include "ofGraphics.h"
#include "ofImage.h"
#include "Projectile.h"

class Alien {
public:
	enum class Type{ bottom, middle, top };
	ofRectangle collision;
private:
	ofImage myAvatar;
	Coordinate myCoordinate;
	Type myType;
	bool isAlienAlive;
public:
	Alien(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{ type } {
		setSprite();
		collision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), myAvatar.getWidth(), myAvatar.getHeight() };
		isAlienAlive = true;
	}


	void draw() const {
		ofSetColor(255);
		myAvatar.draw(myCoordinate.x, myCoordinate.y);
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

	Coordinate getCoordinate() const {
		return myCoordinate;
	}

	void update(Coordinate changeInCoordinate) {
		myCoordinate.x += changeInCoordinate.x;
		myCoordinate.y += changeInCoordinate.y;
		if (isAlienAlive) {
			if (ofGetRectMode() == OF_RECTMODE_CENTER) {
				// ofRectangle intersect() doesn't seem to work with OF_RECTMODE_CENTER
				collision.setX(myCoordinate.x - myAvatar.getWidth() / 2);
				collision.setY(myCoordinate.y - myAvatar.getHeight() / 2);
			}
			else {
				collision.setX(myCoordinate.x);
				collision.setY(myCoordinate.y);
			}
		} else {
			collision.setX(-99);
			collision.setY(-99);
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

private:
	void setSprite() {
		switch(myType) {
		case Type::top:
			myAvatar.load("Assets/yellowAlienShip.png");
			break;
		case Type::middle:
			myAvatar.load("Assets/purpleAlienShip.png");
			break;
		case Type::bottom:
			myAvatar.load("Assets/redAlienShip.png");
			break;
		}
		myAvatar.resize(50, 50);
	}
};
