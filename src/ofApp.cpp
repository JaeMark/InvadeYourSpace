#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetBackgroundColor(10);
	ofSetFrameRate(24);

	ofTrueTypeFont::setGlobalDpi(72);
	title.load("Blanka-Regular.ttf", 50, true, true);
	title.setLineHeight(34.0f);
	title.setLetterSpacing(1.035);
}

//--------------------------------------------------------------
void ofApp::update() {
	manageLoseCondition();
	manageWinCondition();
	cleanUpProjectiles();
	alienSwarm.update();
	alienSwarm.loadProjectile(attackProbability);
	manageAlienCollisions();
	manageHeroCollisions();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(225);

	// draw dividing lines
	const int offsetX = 30;
	ofDrawLine(offsetX, upperBoundary, ofGetWidth() - offsetX, upperBoundary);
	ofDrawLine(offsetX, lowerBoundary, ofGetWidth() - offsetX, lowerBoundary);

	// draw game title
	// align game title to the centre
	const float titlePositionX = ofGetWidth() / 2 - 175; 
	const float titlePositionY = upperBoundary / 2 + title.getLineHeight() / 2; 
	title.drawString("SPACE INVADERS", titlePositionX, titlePositionY);

	// draw player
	player.drawPlayer();

	// draw score
	player.drawScore();

	// draw health
	player.drawHealth();

	// draw player projectiles
	player.updateProjectiles();

	// draw alien swarm
	alienSwarm.draw();

	// draw enemy projectiles
	alienSwarm.drawProjectiles();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'a') {
		player.updateCoordinateX(-heroMovementSpeed, leftBoundary, rightBoundary);
	}
	if (key == 'd') {
		player.updateCoordinateX(heroMovementSpeed, leftBoundary, rightBoundary);
	}
	if (key == 'w') {
		player.addProjectile();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	player.setCoordinateX(x, leftBoundary, rightBoundary);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	player.addProjectile();
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

void ofApp::cleanUpProjectiles() {
	player.cleanUpProjectiles(upperBoundary);
	alienSwarm.cleanUpProjectiles(lowerBoundary);
}

void ofApp::manageAlienCollisions() {
	for (int n{ 0 }; n < alienRow; n++) {
		for (int m{ 0 }; m < alienColumn; m++) {
			for (int j{ 0 }; j < player.getProjectiles().size(); j++) {
				if (player.isProjectileOverlapping(j, alienSwarm.getAlienCollision(n, m)) && alienSwarm.isAlienAlive(n, m)) {
					player.updateScore(alienSwarm.getAlienScore(n, m));
					player.destroyProjectile(j);
					alienSwarm.destroyAlien(n, m);
				}
			}
		}
	}
}

void ofApp::manageHeroCollisions() {
	for (size_t i{ 0 }; i < alienSwarm.getNumProjectile(); i++) {
		if (player.isOverlapping(alienSwarm.getProjectileCollision(i))) {
			player.updateHealth(enemyProjectileDamage);
			alienSwarm.destroyProjectile(i);
		}
	}
}

void ofApp::manageWinCondition() const {
	if(alienSwarm.isDestroyed()) {
		std::cout << "YOU WIN!!" << "\n";
	}
}
void ofApp::manageLoseCondition() const {
	// player loses if its life reaches 0
	// player loses if the alien swarm has reached its location (minus a small offset)
	const int loseBoundary{ static_cast<int>(heroCoordinateY - 50) }; 
	if (player.isDead() || alienSwarm.hasReached(loseBoundary)) {
		std::cout << "YOU LOSE!!" << "\n";
	}
}
