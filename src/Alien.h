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
	Coordinate myCoordinate;
	Type myType;
	ofImage myAvatar;
	ofSoundPlayer myDestructionAudio;
	bool isAlienAlive;
public:
	Alien(const Coordinate& coordinate, const Type& type);

	void draw() const;
	void update(Coordinate changeInCoordinate);
	void destroy();

	int getValue() const;
	Coordinate getWeaponCoordinate() const;

	bool isAlive() const;
	bool isOnBoundary(double leftBoundary, double rightBoundary) const;
private:
	void loadSprite();
};
