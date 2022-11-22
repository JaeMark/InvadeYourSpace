#include "AlienSwarm.h"

AlienSwarm::AlienSwarm(const int& row, const int& column, const int& gridSize, const int& leftBoundary,
	const int& rightBoundary, const Coordinate& initialSpeed, const std::vector<Projectile>& projectiles): myRow{ row }, myColumn{ column }, myGridSize{ gridSize }, myLeftBoundary{ leftBoundary }, myRightBoundary{ rightBoundary }, mySpeed{ initialSpeed }, myProjectiles { projectiles } {
	initializeSwarm();
}

void AlienSwarm::draw() const {
	for (auto& aliens : mySwarm) {
		for (auto& alien : aliens) {
			if (alien.isAlive()) {
				alien.draw();
			}
		}
	}
}

void AlienSwarm::drawProjectiles() {
	for (auto& projectile : myProjectiles) {
		projectile.draw();
	}
}

void AlienSwarm::update() {
	const Coordinate newSpeed = getNewSwarmSpeed();
	for (auto& aliens : mySwarm) {
		for (auto& alien : aliens) {
			alien.update(newSpeed);
		}
	}
}

void AlienSwarm::loadProjectile(const float& loadProbability) {
	// an alien in the swarm has a random chance of launching a projectile
	const float randomNumber = ofRandomuf(); // random number from 0-1;
	if (randomNumber < loadProbability) {
		const Coordinate alienCoordinate = getAvailableAlienCoordinate();
		myProjectiles.emplace_back(Projectile{ alienCoordinate, Projectile::Type::enemy });
	}
}

void AlienSwarm::cleanUpProjectiles(const int boundary) {
	// clean up all projectiles that has reached the given boundary
	for (int i{ 0 }; i < myProjectiles.size(); i++) {
		// find lower edge of the projectile collision
		// myProjectiles[i].collision.getPosition().y will give the y value of the upper left corner of the collision
		// so add the height of the collision to find the lower edge y value
		const int lowerEdge = myProjectiles[i].collision.getPosition().y + myProjectiles[i].collision.getHeight();
		if (lowerEdge > boundary) {
			destroyProjectile(i);
		}
	}
}

void AlienSwarm::destroyAlien(const int n, const int m) {
	mySwarm[n][m].destroy();
	--myLivingAliensCount;
	// speed up every 5 aliens destroyed
	if(myLivingAliensCount % 5 == 0) speedUp();
}

void AlienSwarm::destroyProjectile(int index) {
	myProjectiles.erase(myProjectiles.begin() + index);

}

int AlienSwarm::getAlienScore(const int n, const int m) const {
	return mySwarm[n][m].getValue();
}

size_t AlienSwarm::getNumProjectile() const {
	return myProjectiles.size();
}

ofRectangle AlienSwarm::getAlienCollision(const int n, const int m) {
	return mySwarm[n][m].collision;
}

ofRectangle AlienSwarm::getProjectileCollision(const int index) const {
	return myProjectiles[index].collision;
}

bool AlienSwarm::isDestroyed() const {
	return myLivingAliensCount == 0;
}

bool AlienSwarm::isAlienAlive(const int n, const int m) const {
	return mySwarm[n][m].isAlive();
}

bool AlienSwarm::hasReached(const int& boundary) const {
	// check if the swarm has reached the given boundary
	for (auto& aliens : mySwarm) {
		for (auto& alien : aliens) {
			if (alien.isAlive() && alien.getWeaponCoordinate().y > boundary) {
				return true;
			}
		}
	}
	return false;
}

void AlienSwarm::initializeSwarm() {
	// create alien matrix
	double alienPosX = 0;
	double alienPosY = 0;
	const double gridInitialPosX = ofGetWidth() / 2 - myGridSize * myRow;
	const double gridInitialPosY = 150;
	Alien::Type alienType;
	for (int n{ 0 }; n < myRow; n++) {
		std::vector<Alien> aliens; // row of aliens
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
			++myLivingAliensCount;
		}
		mySwarm.push_back(aliens);
	}
}

Coordinate AlienSwarm::getNewSwarmSpeed() {
	for (auto& aliens : mySwarm) {
		for (auto& alien : aliens) {
			if (alien.isOnBoundary(myLeftBoundary, myRightBoundary)) {
				// change alien swarm horizontal direction and move down
				mySpeed.x *= -1;
				return Coordinate{mySpeed.x, mySpeed.y };
			}
		}
	}
	// no change in direction
	return Coordinate{ mySpeed.x, 0 };
}

Coordinate AlienSwarm::getAvailableAlienCoordinate() const {
	// find all living aliens and return the coordinates of a random one
	std::vector<Alien> aliveAliens;
	for (auto& aliens : mySwarm) {
		for (auto& alien : aliens) {
			if(alien.isAlive()) {
				aliveAliens.push_back(alien);
			}
		}
	}
	return aliveAliens[ofRandom(0, aliveAliens.size())].getWeaponCoordinate();
}

void AlienSwarm::speedUp() {
	// speed up horizontally by 25%
	mySpeed.x *= 1.25;
	// speed up vertically by 10%
	mySpeed.y *= 1.1;
}
