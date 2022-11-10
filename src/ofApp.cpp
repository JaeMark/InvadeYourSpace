#include "ofApp.h"

#include "Projectile.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetWindowShape(750, 550);
	ofSetRectMode(OF_RECTMODE_CENTER);

	// create alien matrix
	double alienPosX = 0;
	double alienPosY = 0;
	double gridInitialPosX = ofGetWidth()/2 - gridSize*alienRow;
	double gridInitialPosY = 100;
	Alien::Type alienType;
	for (int n{ 0 }; n < alienRow; n++) {
		alienPosY = gridSize*n + gridInitialPosY;
		// determine alien type
		if (n == 0) {
			alienType = Alien::Type::top;
		} else if (n == 1 || n == 2) {
			alienType = Alien::Type::middle;
		}
		else if (n == 3 || n == 4) {
			alienType = Alien::Type::bottom;
		}
		for (int m{ 0 }; m < alienColumn; m++) {
			alienPosX = gridSize*m + gridInitialPosX;
			aliens.emplace_back(Alien{ Coordinate{alienPosX, alienPosY}, alienType });
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	checkBoundary();
	checkCollisions();

	// check if the alien swarm has reached the edge
	bool moveDown = false;
	for (auto& alien : aliens) {
		if (alien.isOnBoundary(leftBoundary, rightBoundary)) {
			moveDown = true;
			alienSpeedX *= -1;
			break;
		}
	}
	// move the alien swarm
	for (auto& alien : aliens) {
		if (moveDown) {
			alien.update({ alienSpeedX , alienSpeedY });
		} else {
			alien.update({ alienSpeedX , 0 });
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// draw player
	ofSetColor(255);
	ofDrawRectangle(heroCoordinate.x, heroCoordinate.y, 20, 10);

	// draw score
	heroScore.draw();

	// draw projectiles
	for (auto& heroProjectile : heroProjectiles) {
		heroProjectile.draw();
	}
	// draw alien swarm
	for (auto& alien : aliens) {
		alien.draw();

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'a') {
		heroCoordinate.x -= heroMovementSpeed;
	}
	if (key == 'd') {
		heroCoordinate.x += heroMovementSpeed;
	}
	if (key == 'w') {
		heroProjectiles.push_back(Projectile{ heroCoordinate, Projectile::Type::friendly });
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	heroCoordinate.x = x;

	/* Movement speed based movement
	if (x < heroCoordinate.x) {
		heroCoordinate.x -= heroMovementSpeed;
	}
	if (x > heroCoordinate.x) {
		heroCoordinate.x += heroMovementSpeed;
	}
	*/
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	heroProjectiles.push_back(Projectile{ heroCoordinate, Projectile::Type::friendly });
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::checkBoundary() {
	if (heroCoordinate.x < leftBoundary) {
		heroCoordinate.x = leftBoundary;
	}
	if (heroCoordinate.x > rightBoundary) {
		heroCoordinate.x = rightBoundary;
	}
}

void ofApp::checkCollisions() {
	for (int i{ 0 }; i < aliens.size(); i++) {
		for (int j{ 0 }; j < heroProjectiles.size(); j++) {
			if (heroProjectiles[j].collision.intersects(aliens[i].collision)) {
				heroScore.update(aliens[i].value());
				aliens.erase(aliens.begin() + i);
				heroProjectiles.erase(heroProjectiles.begin() + j);
			}
		}
	}
}