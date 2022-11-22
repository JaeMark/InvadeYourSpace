#include "Projectile.h"

Projectile::Projectile(const Coordinate& coordinate, const Type& type): myCoordinate{ coordinate }, myType{type} {
	setSprite();
	collision = ofRectangle{static_cast<float>(myCoordinate.x), static_cast<float>(myCoordinate.y), myAvatar.getWidth(), myAvatar.getHeight() };
}

void Projectile::draw() {
	update();
	myAvatar.draw(myCoordinate.x, myCoordinate.y);
}

void Projectile::update() {
	myCoordinate.y += mySpeed;
	if (ofGetRectMode() == OF_RECTMODE_CENTER) {
		// ofRectangle intersect() doesn't seem to work with OF_RECTMODE_CENTER
		// offset collision coordinates by half the avatar's width and height
		collision.setX(myCoordinate.x - myAvatar.getWidth() / 2);
		collision.setY(myCoordinate.y - myAvatar.getHeight() / 2);
	}
	else {
		collision.setY(myCoordinate.y);
	}
}

void Projectile::update(const Coordinate coord) {
	myCoordinate = coord;
	if (ofGetRectMode() == OF_RECTMODE_CENTER) {
		// ofRectangle intersect() doesn't seem to work with OF_RECTMODE_CENTER
		// offset collision coordinates by half the avatar's width and height
		collision.setX(coord.x - myAvatar.getWidth() / 2);
		collision.setY(coord.y - myAvatar.getHeight() / 2);
	}
	else {
		collision.setX(coord.x);
		collision.setY(coord.y);
	}
}

void Projectile::setSprite() {
	if (myType == Type::friendly) {
		myAvatar.load("Assets/playerProjectile.png");
		mySpeed = -5;
		myAvatar.rotate90(3);
	}
	else if (myType == Type::enemy) {
		myAvatar.load("Assets/enemyProjectile.png");
		mySpeed = 2;
		myAvatar.rotate90(1);
	}
	myAvatar.resize(20, 40);
}
