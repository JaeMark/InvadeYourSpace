#pragma once
#include <iostream>
#include "Coordinate.h"
#include "ofGraphics.h"
#include "ofTrueTypeFont.h"

class Score {
	int myScore;
	ofTrueTypeFont	myFont;
	const Coordinate myPosition;
public:
	Score(const int& score, const Coordinate& position)
		: myScore{ score }, myPosition { position } {
		myFont.load("Blanka-Regular.ttf", 30, true, true);
		myFont.setLineHeight(34.0f);
		myFont.setLetterSpacing(1.035);
	}

	void draw() const {
		ofSetColor(225);
		myFont.drawString("Player Score: " + ofToString(myScore), myPosition.x, myPosition.y);
	}

	void update(int score) {
		myScore += score;
	}
};
