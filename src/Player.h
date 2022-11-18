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

	void draw() {
		ofSetColor(255);
		myAvatar.setX(myCoordinate.x);
		myAvatar.setY(myCoordinate.y);
		ofDrawRectangle(myAvatar);
	}

	void updateCoordinateX(const double deltaX) {
		myCoordinate.x += deltaX;
		myCollision.setX(myCoordinate.x);
	}

	void updateHealth(const int damage) {
		myHealth.loseHealth(damage);
	}

	void updateScore(const int deltaScore) {
		myScore.update(deltaScore);
	}

	void updateProjectiles() {
		for (auto& projectile : myProjectiles) {
			projectile.draw();
		}
	}

	void addProjectile() {
		myProjectiles.emplace_back(Projectile{ myCoordinate, Projectile::Type::friendly });
	}

	void destroyProjectile(int index) {
		myProjectiles.erase(myProjectiles.begin() + index);
	}

	std::vector<Projectile> getProjectiles() {
		return myProjectiles;
	}

	Coordinate getCoordinate() const {
		return myCoordinate;
	}

	void setCoordinateX(const double x) {
		myCoordinate.x = x;
		myCollision.setX(myCoordinate.x);
	}

	bool isOverlapping(const ofRectangle& otherCollision) const {
		return myCollision.intersects(otherCollision);
	}

	bool isProjectileOverlapping(const int index, const ofRectangle& otherCollision) const {
		return myProjectiles[index].collision.intersects(otherCollision);
	}

	bool isDead() const {
		return myHealth.isDepleted();
	}
};
