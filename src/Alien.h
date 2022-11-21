#pragma once
#include "Coordinate.h"
#include "ofGraphics.h"
#include "ofImage.h"
#include "ofSoundPlayer.h"
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
	ofSoundPlayer myDestructionAudio;
public:
	Alien(const Coordinate& coordinate, const Type& type)
		: myCoordinate{ coordinate }, myType{ type } {
		setSprite();
		collision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), myAvatar.getWidth(), myAvatar.getHeight() };
		isAlienAlive = true;
		myDestructionAudio.load("Audio/alienShipExplosion.mp3");
	}

	void draw() const {
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

	Coordinate getWeaponCoordinate() const {
		// weapon is located at the middle front of the ship
		return Coordinate{ myCoordinate.x, myCoordinate.y + myAvatar.getHeight() / 2 };
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
		myDestructionAudio.play();
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
		myAvatar.resize(40, 40);
	}
};
