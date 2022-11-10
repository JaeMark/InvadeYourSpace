#pragma once
#include <iostream>

class Score {
	int myScore;
public:
	Score(const int& score)
		: myScore{ score } {}

	void draw() {
		std::cout << myScore << "\n";
	}

	void update(int score) {
		myScore += score;
	}
};
