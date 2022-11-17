#pragma once

class Health {
	int myHealth;
public:
	Health(const int& lives)
		: myHealth{ lives } {}

	bool isDepleted() const {
		return myHealth <= 0;
	}

	void loseHealth(const int damage) {
		myHealth += damage;
	}
};
