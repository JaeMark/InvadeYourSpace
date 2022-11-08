#include "ofApp.h"

#include "Projectile.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetWindowShape(750, 550);
	ofSetRectMode(OF_RECTMODE_CENTER);

	double alienPosX = 0;
	double alienPosY = 0;
	for (int n{ 0 }; n < alienRow; n++) {
		alienPosY = 100 * n;
		for (int m{ 0 }; m < alienColumn; m++) {
			alienPosX = 50 * m;
			aliens.push_back(Alien{ Coordinate{alienPosX, alienPosY}, Alien::Type::top });
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	checkBoundary();
	checkCollisions();

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255);
	ofDrawRectangle(heroCoordinate.x, heroCoordinate.y, 20, 10);
	for (auto& heroProjectile : heroProjectiles) {
		heroProjectile.draw();
	}
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
				aliens.erase(aliens.begin() + i);
				heroProjectiles.erase(heroProjectiles.begin() + j);
			}
		}
	}
}