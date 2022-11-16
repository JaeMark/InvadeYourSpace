#pragma once

class Health {
	int myLives;
public:
	Health(const int& lives)
		: myLives{ lives } {}

	bool isDepleted() const {
		return myLives <= 0;
	}

	void loseHealth() {
		--myLives;
	}
};
