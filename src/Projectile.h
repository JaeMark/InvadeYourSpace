#pragma once
#include "Coordinate.h"
#include "ofGraphics.h"
#include "ofImage.h"

class Projectile {
public:
	enum class Type { friendly, enemy };
	ofRectangle collision;
private:
	ofImage myAvatar;
	Coordinate myCoordinate;
	int mySpeed;
	Type myType;
public:
	Projectile(const Coordinate& coordinate, const Type& type);

	void draw();
	void update();
	void update(const Coordinate coord);

private:
	void setSprite();
};
