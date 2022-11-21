#pragma once
#include "Coordinate.h"
#include "ofTrueTypeFont.h"

class Health {
	int myHealth;
	ofTrueTypeFont myFont;
	const Coordinate myPosition;
public:
	Health(const int& lives, const Coordinate& position)
		: myHealth{ lives }, myPosition{ position } {
		myFont.load("Blanka-Regular.ttf", 30, true, true);
		myFont.setLineHeight(34.0f);
		myFont.setLetterSpacing(1.035);
	}

	void draw() {
		myFont.drawString("HEALTH: " + ofToString(myHealth), myPosition.x, myPosition.y + myFont.getLineHeight() / 2);
	}

	bool isDepleted() const {
		return myHealth <= 0;
	}

	void loseHealth(const int damage) {
		myHealth += damage;
	}
};
