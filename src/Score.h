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
	Score(const int& score, const Coordinate& position);

	void draw() const;
	void update(const int score);
};
