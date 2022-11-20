#pragma once
#include <iostream>
#include "Coordinate.h"
#include "ofBitmapFont.h"
#include "ofTrueTypeFont.h"

class Score {
	int myScore;
	const Coordinate myPosition;
	ofTrueTypeFont	myFont;
public:
	Score(const int& score, const Coordinate& position)
		: myScore{ score }, myPosition{ position } {
		myFont.load("verdana.ttf", 30, true, true);
		myFont.setLineHeight(34.0f);
		myFont.setLetterSpacing(1.035);
	}

	void draw() {
		//ofDrawBitmapString("Player Score: " + ofToString(myScore), myPosition.x, myPosition.y);
		ofSetColor(225);
		myFont.drawString("verdana 30pt - ", myPosition.x, myPosition.y);

		//ofDrawLine(30, myPosition.y + 50, ofGetWidth() - 30, myPosition.y + 50);
		//myFont.drawString(typeStr, 30, 229);
	}

	void update(int score) {
		myScore += score;
	}
};
