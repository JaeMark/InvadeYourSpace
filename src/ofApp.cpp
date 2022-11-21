#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetBackgroundColor(10);
	ofSetFrameRate(24);

	// setup title font
	ofTrueTypeFont::setGlobalDpi(72);
	title.load("Blanka-Regular.ttf", 50, true, true);
	title.setLineHeight(34.0f);
	title.setLetterSpacing(1.035);
}

//--------------------------------------------------------------
void ofApp::update() {
	if(gameState == GameState::playing) {
		manageLoseCondition();
		manageWinCondition();
		cleanUpProjectiles();
		alienSwarm.update();
		alienSwarm.loadProjectile(attackProbability);
		manageAlienCollisions();
		manageHeroCollisions();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(225);

	// draw border lines
	const int offsetX = 30;
	ofDrawLine(offsetX, upperBoundary, ofGetWidth() - offsetX, upperBoundary);
	ofDrawLine(offsetX, lowerBoundary, ofGetWidth() - offsetX, lowerBoundary);

	// draw game title; align game title to the centre
	const float titlePositionX = ofGetWidth() / 2 - 175; 
	const float titlePositionY = upperBoundary / 2 + title.getLineHeight() / 2; 
	title.drawString("SPACE INVADERS", titlePositionX, titlePositionY);

	// draw score
	player.drawScore();
	// draw health
	player.drawHealth();

	// handle game states
	switch(gameState) {
	case GameState::start:
		break;
	case GameState::playing:
		// draw player
		player.drawPlayer();
		// draw player projectiles
		player.drawProjectiles();
		// draw alien swarm
		alienSwarm.draw();
		// draw enemy projectiles
		alienSwarm.drawProjectiles();
		break;
	case GameState::won:
		// draw player
		player.drawPlayer();

		break;
	case GameState::lost:
		// draw alien swarm
		alienSwarm.draw();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (gameState == GameState::playing) {
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
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if(gameState == GameState::playing) {
		player.setCoordinateX(x, leftBoundary, rightBoundary);
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (gameState == GameState::playing) {
		player.addProjectile();
	}
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
	// clean up projectiles outside the game boundaries
	player.cleanUpProjectiles(upperBoundary);
	alienSwarm.cleanUpProjectiles(lowerBoundary);
}

void ofApp::manageAlienCollisions() {
	// check if any player projectile and alien collisions are intersecting
	// destroy any that do
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
	// check if any alien projectile hit the player
	// destroy the projectile and damage the player if so
	for (size_t i{ 0 }; i < alienSwarm.getNumProjectile(); i++) {
		if (player.isOverlapping(alienSwarm.getProjectileCollision(i))) {
			player.updateHealth(enemyProjectileDamage);
			alienSwarm.destroyProjectile(i);
		}
	}
}

void ofApp::manageWinCondition() {
	// player wins if all the aliens have been destroyed
	if(alienSwarm.isDestroyed()) {
		gameState = GameState::won;
	}
}
void ofApp::manageLoseCondition() {
	// player loses if its life reaches 0
	// player loses if the alien swarm has reached its location (minus a small offset to account for the sprite height)
	const int loseBoundary{ static_cast<int>(heroCoordinateY - 50) }; 
	if (player.isDead() || alienSwarm.hasReached(loseBoundary)) {
		gameState = GameState::lost;
	}
}
