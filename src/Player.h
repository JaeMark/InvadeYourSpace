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
	std::vector<Projectile> myProjectiles;
public:
	Player(const ofRectangle& avatar, const Coordinate& coordinate, const Health& health, const Score& score, const std::vector<Projectile>& projectiles)
		: myAvatar{ avatar }, myCoordinate{ coordinate }, myHealth{ health }, myScore{ score }, myProjectiles{ projectiles } {
		myCollision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), 10, 10 };
	}

	void updateCoordinate(const double deltaX) {
		myCoordinate.x += deltaX;
		myCollision.setX(myCoordinate.x);
	}

	void updateHealth(const int damage) {
		myHealth.loseHealth(damage);
	}

	void updateScore(const int deltaScore) {
		myScore.update(deltaScore);
	}

	void addProjectile(const Projectile& projectile) {
		myProjectiles.push_back(projectile);
	}

	void deleteProjectile(int index) {
		myProjectiles.erase(myProjectiles.begin() + index);
	}

	bool isProjectileOverlapping(const int index, const ofRectangle& otherCollision) {
		return myProjectiles[index].collision.intersects(otherCollision);
	}

	bool isPlayerDead() {
		return myHealth.isDepleted();
	}
};
