#pragma once
#include "Coordinate.h"
#include "Health.h"
#include "ofRectangle.h"
#include "Projectile.h"
#include "Score.h"

class Player {
public:
	ofRectangle myCollision;
private:
	ofRectangle myAvatar;
	Coordinate myCoordinate;
	Health myHealth;
	Score myScore;
	int myMovementSpeed;
	std::vector<Projectile> myProjectiles;
public:
	Player(const ofRectangle& avatar, const Coordinate& coordinate, const Health& health, const Score& score, const int& movementSpeed, const std::vector<Projectile>& projectiles)
		: myAvatar{ avatar }, myCoordinate{ coordinate }, myHealth{ health }, myScore{ score }, myMovementSpeed{ movementSpeed }, myProjectiles{ projectiles } {
		myCollision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), 10, 10 };
	}
};
