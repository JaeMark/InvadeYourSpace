#pragma once
#include "Coordinate.h"
#include "Health.h"
#include "ofImage.h"
#include "ofRectangle.h"
#include "Projectile.h"
#include "Score.h"

class Player {
public:
	ofRectangle myCollision;
private:
	ofImage myAvatar;
	Coordinate myCoordinate;
	Health myHealth;
	Score myScore;
	std::vector<Projectile> myProjectiles;
public:
	Player(const std::string& avatarName, const Coordinate& coordinate, const Health& health, const Score& score, const std::vector<Projectile>& projectiles)
		: myCoordinate{ coordinate }, myHealth{ health }, myScore{ score }, myProjectiles{ projectiles } {
		myAvatar.load(avatarName);
		myAvatar.resize(68, 42);
		myCollision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), myAvatar.getWidth(), myAvatar.getHeight() };
	}

	void drawPlayer() const {
		myAvatar.draw(myCoordinate.x, myCoordinate.y);
	}

	void drawScore() const {
		myScore.draw();
	}

	void drawHealth() {
		myHealth.draw();
	}

	void updateCoordinateX(const double deltaX, const int& leftBoundary, const int& rightBoundary) {
		myCoordinate.x += deltaX;
		myCoordinate.x = ofClamp(myCoordinate.x, leftBoundary, rightBoundary);
		if(ofGetRectMode() == OF_RECTMODE_CENTER) {
			myCollision.setX(myCoordinate.x - myAvatar.getWidth() / 2);
		} else {
			myCollision.setX(myCoordinate.x);
		}
	}

	void updateHealth(const int damage) {
		myHealth.loseHealth(damage);
	}

	void updateScore(const int deltaScore) {
		myScore.update(deltaScore);
	}

	void drawProjectiles() {
		for (auto& projectile : myProjectiles) {
			projectile.draw();
		}
	}

	void addProjectile() {
		// weapon is located at the middle front of the ship
		const Coordinate weaponCoordinate{ myCoordinate.x, myCoordinate.y - myAvatar.getHeight() / 2 };
		myProjectiles.emplace_back(Projectile{ weaponCoordinate, Projectile::Type::friendly });
	}

	void destroyProjectile(int index) {
		myProjectiles.erase(myProjectiles.begin() + index);
	}

	void cleanUpProjectiles(const int boundary) {
		// check if the upper edge of each projectile has reached the given boundary
		// destroy the projectile if it has
		for (int i{ 0 }; i < myProjectiles.size(); i++) {
			if (myProjectiles[i].collision.getPosition().y < boundary) {
				destroyProjectile(i);
			}
		}
	}

	std::vector<Projectile> getProjectiles() {
		return myProjectiles;
	}

	Coordinate getCoordinate() const {
		return myCoordinate;
	}

	void setCoordinateX(const double x, const int& leftBoundary, const int& rightBoundary) {
		myCoordinate.x = x;
		myCoordinate.x = ofClamp(myCoordinate.x, leftBoundary, rightBoundary);
		if (ofGetRectMode() == OF_RECTMODE_CENTER) {
			// ofRectangle intersect() doesn't seem to work with OF_RECTMODE_CENTER
			myCollision.setX(myCoordinate.x - myAvatar.getWidth() / 2);
			myCollision.setY(myCoordinate.y - myAvatar.getHeight() / 2);
		} else {
			myCollision.setX(myCoordinate.x);
		}
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
