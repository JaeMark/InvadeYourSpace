#pragma once
#include "Alien.h"
#include "ofAppRunner.h"

class AlienSwarm {
	const int myRow;
	const int myColumn;
	const int myGridSize;
	const int myLeftBoundary;
	const int myRightBoundary;
	std::vector<std::vector<Projectile>> myProjectiles;
	std::vector<std::vector<Alien>> mySwarm;
public:
	AlienSwarm(const int& row, const int& column, const int& gridSize, const int& leftBoundary, const int& rightBoundary, const std::vector<std::vector<Projectile>>& projectiles)
		: myRow{ row }, myColumn{ column }, myGridSize{ gridSize }, myLeftBoundary{ leftBoundary }, myRightBoundary{ rightBoundary }, myProjectiles{ projectiles } {
		initalizeSwarm();
	}

	void initalizeSwarm() {
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
};
/*
const int alienRow{ 5 };
const int alienColumn{ 11 };
const int gridSize = 50;
std::vector<vector<Alien>> alienSwarm;
int numAliens{ alienRow * alienColumn };
std::vector<int> alienBomberRow; // available bombers
Projectile alienProjectile{ {0, 0}, Projectile::Type::enemy };
bool isBomberAssigned = false;
const int enemyProjectileDamage = -1
*/