#include "Health.h"

Health::Health(const int& lives, const Coordinate& position): myHealth{ lives }, myPosition{ position } {
	myFont.load("Blanka-Regular.ttf", 30, true, true);
	myFont.setLineHeight(34.0f);
	myFont.setLetterSpacing(1.035);
}

void Health::draw() const {
	myFont.drawString("HEALTH: " + ofToString(myHealth), myPosition.x, myPosition.y + myFont.getLineHeight() / 2);
}

void Health::loseHealth(const int damage) {
	myHealth += damage;
}

bool Health::isDepleted() const {
	return myHealth <= 0;
}
