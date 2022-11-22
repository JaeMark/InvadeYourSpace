#pragma once
#include "Coordinate.h"
#include "Health.h"
#include "ofImage.h"
#include "ofRectangle.h"
#include "ofSoundPlayer.h"
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
	ofSoundPlayer myHitAudio;
public:
	Player(const std::string& avatarName, const Coordinate& coordinate, const Health& health, const Score& score, const std::vector<Projectile>& projectiles);

	void drawPlayer() const;
	void drawScore() const;
	void drawHealth() const;
	void drawProjectiles();

	void updateCoordinateX(const double deltaX, const int& leftBoundary, const int& rightBoundary);
	void updateHealth(const int damage);
	void updateScore(const int deltaScore);

	void addProjectile();
	void destroyProjectile(int index);
	void cleanUpProjectiles(const int boundary);

	std::vector<Projectile> getProjectiles();
	Coordinate getCoordinate() const;

	void setCoordinateX(const double x, const int& leftBoundary, const int& rightBoundary);

	bool isOverlapping(const ofRectangle& otherCollision) const;
	bool isProjectileOverlapping(const int index, const ofRectangle& otherCollision) const;
	bool isDead() const;
};
