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

	void draw() {
		ofSetColor(255);
		myAvatar.draw(myCoordinate.x, myCoordinate.y);
	}

	void updateCoordinateX(const double deltaX) {
		myCoordinate.x += deltaX;
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
