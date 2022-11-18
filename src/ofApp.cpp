#include "ofApp.h"

#include "Projectile.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetWindowShape(750, 550);
	ofSetRectMode(OF_RECTMODE_CENTER);

	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update() {
	manageHorizontalBoundaries();
	manageVerticalBoundaries();
	manageAlienCollisions();
	manageHeroCollisions();
	manageLoseCondition();
	manageWinCondition();

	alienSwarm.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	// draw player
	player.draw();

	// draw score
	//heroScore.draw();

	// draw player projectiles
	player.updateProjectiles();

	// draw enemy projectiles
	alienSwarm.drawProjectiles();

	// draw alien swarm
	alienSwarm.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'a') {
		player.updateCoordinateX(-heroMovementSpeed);
	}
	if (key == 'd') {
		player.updateCoordinateX(heroMovementSpeed);
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
	player.setCoordinateX(x);
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

void ofApp::assignBomber() {
	const float randomNumber = ofRandomf(); // random number from 0-1;
	//if (randomNumber < attackProbability) {
		alienSwarm.addProjectile();
	//}
}

void ofApp::manageVerticalBoundaries() {
	const std::vector<Projectile> playerProjectiles{ player.getProjectiles() };
	for (int i{ 0 }; i < playerProjectiles.size(); i++) {
		if(playerProjectiles[i].collision.getPosition().y < upperBoundary) {
			// clean up projectiles out of bounds
			player.deleteProjectile(i);
		}
	}
	alienSwarm.cleanUpProjectiles(lowerBoundary);
}

void ofApp::manageHorizontalBoundaries() {
	const double playerCoordinateX = player.getCoordinate().x;
	if (playerCoordinateX < leftBoundary) {
		player.setCoordinateX(leftBoundary);
	}
	if (playerCoordinateX > rightBoundary) {
		player.setCoordinateX(rightBoundary);
	}
}

void ofApp::manageAlienCollisions() {
	for (int n{ 0 }; n < alienRow; n++) {
		for (int m{ 0 }; m < alienColumn; m++) {
			for (int j{ 0 }; j < player.getProjectiles().size(); j++) {
				if (player.isProjectileOverlapping(j, alienSwarm.getAlienCollision(n, m)) && alienSwarm.isAlienAlive(n, m)) {
					player.updateScore(alienSwarm.getAlienScore(n, m));
					player.deleteProjectile(j);
					alienSwarm.destroyAlien(n, m);
				}
			}
		}
	}
}

void ofApp::manageHeroCollisions() {
	for (auto& projectile : alienProjectiles) {
		if (player.isOverlapping(projectile.collision)) {
			player.updateHealth(enemyProjectileDamage);
		}
	}
}

void ofApp::manageWinCondition() const {
	if(alienSwarm.isDestroyed()) {
		std::cout << "YOU WIN!!" << "\n";
	}
}
void ofApp::manageLoseCondition() const {
	if (player.isDead()) {
		std::cout << "YOU LOSE!!" << "\n";
	}
}
