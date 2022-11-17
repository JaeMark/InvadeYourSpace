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
		std::vector<Alien> aliens;
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
			Coordinate alienCoord{ Coordinate{ alienPosX, alienPosY } };
			aliens.emplace_back(Alien{ alienCoord , alienType });
			if(n == alienRow - 1) {
				alienBomberRow.push_back(n);
			}
		}
		alienSwarm.push_back(aliens);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	manageHorizontalBoundaries();
	manageVerticalBoundaries();
	manageAlienCollisions();
	manageHeroCollisions();
	manageLoseCondition();
	manageWinCondition();

	bool moveDown = isOnBoundary();
	for (auto& aliens : alienSwarm) {
		for (auto& alien : aliens) {
			if (moveDown) {
				alien.update({ alienSwarmSpeed.x , alienSwarmSpeed.y });
			}
			else {
				alien.update({ alienSwarmSpeed.x , 0 });
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// draw player
	player.draw();

	// draw score
	//heroScore.draw();

	// draw player projectiles
	/*
	for (auto& heroProjectile : player.getProjectiles()) {
		heroProjectile.draw();
	}
	*/

	player.updateProjectiles();

	// draw enemy projectiles
	if(!isBomberAssigned) {
		assignBomber();
	} 
	alienProjectile.draw();


	// draw alien swarm
	for (auto& aliens : alienSwarm) {
		for (auto& alien : aliens) {
			if(alien.isAlive()) {
				alien.draw();
			}
		}
	}
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
	int chosenBomber = ofRandom(0, alienColumn);
	alienProjectile.update(alienSwarm[alienBomberRow[chosenBomber]][chosenBomber].getCoordinate());
	isBomberAssigned = true;
}

void ofApp::manageVerticalBoundaries() {
	const std::vector<Projectile> playerProjectiles{ player.getProjectiles() };
	for (int i{ 0 }; i < playerProjectiles.size(); i++) {
		if(playerProjectiles[i].collision.getPosition().y < upperBoundary) {
			// clean up projectiles out of bounds
			player.deleteProjectile(i);
		}
	}
	if (alienProjectile.collision.getPosition().y > lowerBoundary) {
		isBomberAssigned = false; // bomber will be reassigned
	}
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
				if (player.isProjectileOverlapping(j, alienSwarm[n][m].collision) && alienSwarm[n][m].isAlive()) {
					player.updateScore(alienSwarm[n][m].value());
					player.deleteProjectile(j);
					alienSwarm[n][m].destroy();
					--numAliens;
				}
			}
		}
	}
}

void ofApp::manageHeroCollisions() {
	if(player.isOverlapping(alienProjectile.collision)) {
		isBomberAssigned = false; // bomber will be reassigned
		player.updateHealth(enemyProjectileDamage);
	}
}

void ofApp::manageWinCondition() {
	if(numAliens <= 0) {
		std::cout << "YOU WIN!!" << "\n";
	}
}
void ofApp::manageLoseCondition() {
	if (player.isDead()) {
		std::cout << "YOU LOSE!!" << "\n";
	}
}


bool ofApp::isOnBoundary() {
	// check if the alien swarm has reached the edge
	bool moveDown = false;
	for (auto& aliens : alienSwarm) {
		for (auto& alien : aliens) {
			if (alien.isOnBoundary(leftBoundary, rightBoundary)) {
				alienSwarmSpeed.x *= -1;
				return true;
			}
		}
	}
	return moveDown;
}
