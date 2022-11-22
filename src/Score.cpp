#include "Score.h"

Score::Score(const int& score, const Coordinate& position): myScore{ score }, myPosition { position } {
	myFont.load("Blanka-Regular.ttf", 30, true, true);
	myFont.setLineHeight(34.0f);
	myFont.setLetterSpacing(1.035);
}

void Score::draw() const {
	ofSetColor(225);
	// since the text is drawn from the bottom left corner
	// add an offset to center the text at myPosition.y
	const double heightOffset = myFont.getLineHeight() / 2; 
	myFont.drawString("PLAYER SCORE: " + ofToString(myScore), myPosition.x, myPosition.y + heightOffset);
}

void Score::update(const int score) {
	myScore += score;
}
