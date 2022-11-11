#include "ofApp.h"

#include "Projectile.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//ofSetWindowShape(750, 550);
	ofSetRectMode(OF_RECTMODE_CENTER);

	// create alien matrix
	double alienPosX = 0;
	double alienPosY = 0;
	double gridInitialPosX = ofGetWidth() / 2 - gridSize * alienRow;
	double gridInitialPosY = 100;
	Alien::Type alienType;
	for (int n{ 0 }; n < alienRow; n++) {
		alienPosY = gridSize * n + gridInitialPosY;
		std::vector<Alien> alienRow;
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
		for (int m{ 0 }; m < alienColumn; m++) {
			alienPosX = gridSize * m + gridInitialPosX;
			alienRow.emplace_back(Alien{ Coordinate{alienPosX, alienPosY}, alienType });
		}
		alienMatrix.push_back(alienRow);
	}
	alienSwarm = AlienSwarm{ alienMatrix, alienRow, alienColumn, initialSwarmSpeed };
}

//--------------------------------------------------------------
void ofApp::update() {
	checkBoundary();
	checkCollisions();
	alienSwarm.moveSwarm(leftBoundary, rightBoundary);
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
	alienSwarm.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a') {
		// move left
		heroCoordinate.x -= heroMovementSpeed;
	}
	if (key == 'd') {
		// move right
		heroCoordinate.x += heroMovementSpeed;
	}
	if (key == 'w') {
		// fire projectile
		heroProjectiles.push_back(Projectile{ heroCoordinate, Projectile::Type::friendly });
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
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
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	heroProjectiles.push_back(Projectile{ heroCoordinate, Projectile::Type::friendly });
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

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
	
	for (int n{ 0 }; n < alienRow; n++) {
		for(int m{ 0 }; m < alienColumn; m++) {
			for (int j{ 0 }; j < heroProjectiles.size(); j++) {
				if (heroProjectiles[j].collision.intersects(alienSwarm.getAlienCollision(n, m))) {
					heroScore.update(alienSwarm.getAlienValue(n, m));
					alienSwarm.destroyAlien(n, m);
					heroProjectiles.erase(heroProjectiles.begin() + j);
				}
			}
		}
	}
	
}

