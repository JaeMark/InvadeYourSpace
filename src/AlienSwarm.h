#pragma once
#include "Alien.h"
#include "ofAppRunner.h"
#include "ofMath.h"

class AlienSwarm {
private:
	const int myRow;
	const int myColumn;
	const int myGridSize;
	const int myLeftBoundary;
	const int myRightBoundary;
	Coordinate mySpeed;
	std::vector<Projectile> myProjectiles;
	std::vector<std::vector<Alien>> mySwarm;
	int myLivingAliensCount = 0;
public:
	AlienSwarm(const int& row, const int& column, const int& gridSize, const int& leftBoundary, const int& rightBoundary, const Coordinate& initialSpeed, const std::vector<Projectile>& projectiles);

	void draw() const;
	void drawProjectiles();

	void update();

	void loadProjectile(const float& loadProbability);
	void cleanUpProjectiles(const int boundary);

	void destroyAlien(const int n, const int m);
	void destroyProjectile(int index);

	int getAlienScore(const int n, const int m) const;
	size_t getNumProjectile() const;
	ofRectangle getAlienCollision(const int n, const int m);
	ofRectangle getProjectileCollision(const int index) const;

	bool isDestroyed() const;
	bool isAlienAlive(const int n, const int m) const;
	bool hasReached(const int& boundary) const;

private:
	void initializeSwarm();
	Coordinate getNewSwarmSpeed();
	Coordinate getAvailableAlienCoordinate() const;
	void speedUp();
};
