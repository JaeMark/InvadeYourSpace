#pragma once
#include "Coordinate.h"
#include "ofTrueTypeFont.h"

class Health {
	int myHealth;
	const Coordinate myPosition;
	ofTrueTypeFont myFont;
public:
	Health(const int& lives, const Coordinate& position);

	void draw() const;
	void loseHealth(int damage);
	bool isDepleted() const;
};
