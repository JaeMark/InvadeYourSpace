#include "Player.h"

Player::Player(const std::string& avatarName, const Coordinate& coordinate, const Health& health, const Score& score,
	const std::vector<Projectile>& projectiles): myCoordinate{ coordinate }, myHealth{ health }, myScore{ score }, myProjectiles{ projectiles } {
	myAvatar.load(avatarName);
	myAvatar.resize(68, 42);
	myCollision = ofRectangle{ static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), myAvatar.getWidth(), myAvatar.getHeight() };
	myHitAudio.load("Audio/playerHitAudio.mp3");
}

void Player::drawPlayer() const {
	myAvatar.draw(myCoordinate.x, myCoordinate.y);
}

void Player::drawScore() const {
	myScore.draw();
}

void Player::drawHealth() const {
	myHealth.draw();
}

void Player::drawProjectiles() {
	for (auto& projectile : myProjectiles) {
		projectile.draw();
	}
}

void Player::updateCoordinateX(const double deltaX, const int& leftBoundary, const int& rightBoundary) {
	myCoordinate.x += deltaX;
	// prevent the player from leaving the left and right boundaries
	myCoordinate.x = ofClamp(myCoordinate.x, leftBoundary, rightBoundary); 
	if(ofGetRectMode() == OF_RECTMODE_CENTER) {
		// ofRectangle intersect() doesn't seem to work with OF_RECTMODE_CENTER
		// offset collision coordinate x by half the avatar's width
		myCollision.setX(myCoordinate.x - myAvatar.getWidth() / 2);
	} else {
		myCollision.setX(myCoordinate.x);
	}
}

void Player::updateHealth(const int damage) {
	myHealth.loseHealth(damage);
	myHitAudio.play();

}

void Player::updateScore(const int deltaScore) {
	myScore.update(deltaScore);
}

void Player::addProjectile() {
	// weapon is located at the middle front of the ship
	// limit to 1 projectile at a time
	if (myProjectiles.size() == 0) {
		const Coordinate weaponCoordinate{ myCoordinate.x, myCoordinate.y - myAvatar.getHeight() / 2 };
		myProjectiles.emplace_back(Projectile{ weaponCoordinate, Projectile::Type::friendly });
	}
}

void Player::destroyProjectile(int index) {
	myProjectiles.erase(myProjectiles.begin() + index);
}

void Player::cleanUpProjectiles(const int boundary) {
	// check if the upper edge of each projectile has reached the given boundary
	// destroy the projectile if it has
	for (int i{ 0 }; i < myProjectiles.size(); i++) {
		if (myProjectiles[i].collision.getPosition().y < boundary) {
			destroyProjectile(i);
		}
	}
}

std::vector<Projectile> Player::getProjectiles() {
	return myProjectiles;
}

Coordinate Player::getCoordinate() const {
	return myCoordinate;
}

void Player::setCoordinateX(const double x, const int& leftBoundary, const int& rightBoundary) {
	myCoordinate.x = x;
	myCoordinate.x = ofClamp(myCoordinate.x, leftBoundary, rightBoundary);
	if (ofGetRectMode() == OF_RECTMODE_CENTER) {
		// ofRectangle intersect() doesn't seem to work with OF_RECTMODE_CENTER
		// offset collision coordinates by half the avatar's width and height
		myCollision.setX(myCoordinate.x - myAvatar.getWidth() / 2);
		myCollision.setY(myCoordinate.y - myAvatar.getHeight() / 2);
	} else {
		myCollision.setX(myCoordinate.x);
	}
}

bool Player::isOverlapping(const ofRectangle& otherCollision) const {
	return myCollision.intersects(otherCollision);
}

bool Player::isProjectileOverlapping(const int index, const ofRectangle& otherCollision) const {
	return myProjectiles[index].collision.intersects(otherCollision);
}

bool Player::isDead() const {
	return myHealth.isDepleted();
}
