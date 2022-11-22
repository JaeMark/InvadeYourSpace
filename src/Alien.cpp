#include "Alien.h"

Alien::Alien(const Coordinate& coordinate, const Type& type): myCoordinate{ coordinate }, myType{ type } {
	loadSprite();
	collision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), myAvatar.getWidth(), myAvatar.getHeight() };
	isAlienAlive = true;
	myDestructionAudio.load("Audio/alienShipExplosion.mp3");
}

void Alien::draw() const {
	myAvatar.draw(myCoordinate.x, myCoordinate.y);
}

void Alien::update(Coordinate changeInCoordinate) {
	myCoordinate.x += changeInCoordinate.x;
	myCoordinate.y += changeInCoordinate.y;
	if (isAlienAlive) {
		if (ofGetRectMode() == OF_RECTMODE_CENTER) {
			// ofRectangle intersect() doesn't seem to work with OF_RECTMODE_CENTER
			// offset collision coordinates by half the avatar's width and height
			collision.setX(myCoordinate.x - myAvatar.getWidth() / 2);
			collision.setY(myCoordinate.y - myAvatar.getHeight() / 2);
		}
		else {
			collision.setX(myCoordinate.x);
			collision.setY(myCoordinate.y);
		}
	}
	else {
		// can't delete collision, so hide it far away
		collision.setX(-99);
		collision.setY(-99);
	}
}

void Alien::destroy() {
	isAlienAlive = false;
	myDestructionAudio.play();
}

int Alien::getValue() const {
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

Coordinate Alien::getWeaponCoordinate() const {
	// weapon is located at the middle front of the ship
	return Coordinate{ myCoordinate.x, myCoordinate.y + myAvatar.getHeight() / 2 };
}

bool Alien::isAlive() const {
	return isAlienAlive;
}

bool Alien::isOnBoundary(double leftBoundary, double rightBoundary) const {
	// check if the alien has reached the side boundaries
	return (myCoordinate.x <= leftBoundary || myCoordinate.x >= rightBoundary) && isAlienAlive;
}

void Alien::loadSprite() {
	// load alien avatar
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
