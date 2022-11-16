#pragma once

class Health {
	int myLives;
public:
	Health(const int& lives)
		: myLives{ lives } {}

	bool isplayerDead() {
		return myLives <= 0;
	}

	void depleteHealth() {
		--myLives;
	}
};
