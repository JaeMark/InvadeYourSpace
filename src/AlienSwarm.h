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
	int numLivingAliens;
public:
	AlienSwarm(const int& row, const int& column, const int& gridSize, const int& leftBoundary, const int& rightBoundary, const Coordinate& initialSpeed, const std::vector<Projectile>& projectiles)
		: myRow{ row }, myColumn{ column }, myGridSize{ gridSize }, myLeftBoundary{ leftBoundary }, myRightBoundary{ rightBoundary }, mySpeed{ initialSpeed }, myProjectiles { projectiles } {
		initializeSwarm();
		numLivingAliens = myRow * myColumn;
	}

	void draw() const {
		for (auto& aliens : mySwarm) {
			for (auto& alien : aliens) {
				if (alien.isAlive()) {
					alien.draw();
				}
			}
		}
	}

	void update() {
		const Coordinate newSpeed = getNewSwarmSpeed();
		for (auto& aliens : mySwarm) {
			for (auto& alien : aliens) {
				alien.update(newSpeed);
			}
		}
	}

	

	void destroyAlien(const int n, const int m) {
		mySwarm[n][m].destroy();
		--numLivingAliens;
		// speed up every 5 aliens destroyed
		if(numLivingAliens % 5 == 0) speedUp();
	}

	bool isDestroyed() const {
		return numLivingAliens == 0;
	}

	bool isAlienAlive(const int n, const int m) const {
		return mySwarm[n][m].isAlive();
	}

	ofRectangle getAlienCollision(const int n, const int m) {
		return mySwarm[n][m].collision;
	}

	int getAlienScore(const int n, const int m) const {
		return mySwarm[n][m].value();
	}


	// Projectiles
	void drawProjectiles() {
		for (auto& projectile : myProjectiles) {
			projectile.draw();
		}
	}

	void addProjectile() {
		const Coordinate alienCoordinate = getAvailableAlienCoordinate();
		myProjectiles.emplace_back(Projectile{ alienCoordinate, Projectile::Type::enemy });
	}

	void destroyProjectile(int index) {
		myProjectiles.erase(myProjectiles.begin() + index);

	}

	size_t getNumProjectile() const {
		return myProjectiles.size();
	}

	ofRectangle getProjectileCollision(const int index) const {
		return myProjectiles[index].collision;
	}

	void cleanUpProjectiles(const int boundary) {
		for (int i{ 0 }; i < myProjectiles.size(); i++) {
			if (myProjectiles[i].collision.getPosition().y > boundary) {
				destroyProjectile(i);
			}
		}
	}

private:
	void initializeSwarm() {
		// create alien matrix
		double alienPosX = 0;
		double alienPosY = 0;
		const double gridInitialPosX = ofGetWidth() / 2 - myGridSize * myRow;
		const double gridInitialPosY = 100;
		Alien::Type alienType;
		for (int n{ 0 }; n < myRow; n++) {
			std::vector<Alien> aliens;
			alienPosY = myGridSize * n + gridInitialPosY;
			// determine alien type
			if (n == 0) {
				alienType = Alien::Type::top;
			}
			else if (n == 1 || n == 2) {
				alienType = Alien::Type::middle;
			}
			else if (n == 3 || n == 4) {
				alienType = Alien::Type::bottom;
			}
			for (int m{ 0 }; m < myColumn; m++) {
				alienPosX = myGridSize * m + gridInitialPosX;
				Coordinate alienCoord{ Coordinate{ alienPosX, alienPosY } };
				aliens.emplace_back(Alien{ alienCoord , alienType });
			}
			mySwarm.push_back(aliens);
		}
	}

	Coordinate getNewSwarmSpeed() {
		for (auto& aliens : mySwarm) {
			for (auto& alien : aliens) {
				if (alien.isOnBoundary(myLeftBoundary, myRightBoundary)) {
					// change alien swarm velocity
					mySpeed.x *= -1;
					return Coordinate{mySpeed.x, mySpeed.y };
				}
			}
		}
		// no change in velocity direction
		return Coordinate{ mySpeed.x, 0 };
	}

	Coordinate getAvailableAlienCoordinate() const {
		std::vector<Alien> aliveAliens;
		for (auto& aliens : mySwarm) {
			for (auto& alien : aliens) {
				if(alien.isAlive()) {
					aliveAliens.push_back(alien);
				}
			}
		}
		// return random alive alien
		return aliveAliens[ofRandom(0, aliveAliens.size())].getCoordinate();
	}

	void speedUp() {
		// speed up by 25%
		mySpeed.x *= 1.25; 
	}
};
