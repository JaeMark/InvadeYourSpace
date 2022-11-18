#pragma once

#include "Alien.h"
#include "AlienSwarm.h"
#include "Health.h"
#include "ofMain.h"
#include "Player.h"
#include "Projectile.h"
#include "Score.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

private:
	const int leftBoundary = 100;
	const int rightBoundary = ofGetWidth() - 100;
	const int upperBoundary = 0;
	const int lowerBoundary = ofGetHeight();
		
	Coordinate heroCoordinate{ static_cast<double>(ofGetWidth() / 2), 600.0 };
	ofRectangle heroCollision = ofRectangle{ static_cast<float>(heroCoordinate.x), static_cast<float>(heroCoordinate.y), 20, 10 };
	Score heroScore{ 0 };
	Health heroHealth{ 3 };
	std::vector<Projectile> heroProjectiles;
	Player player{ Player{ ofRectangle(heroCoordinate.x, heroCoordinate.y, 20, 10), heroCoordinate, heroHealth, heroScore, heroProjectiles } };
	const int heroMovementSpeed = 10;


	const int alienRow{ 5 };
	const int alienColumn{ 11 };
	const int gridSize = 50;
	Coordinate initialAlienSwarmSpeed{ 1, 5 };
	std::vector<Projectile> alienProjectiles;
	AlienSwarm alienSwarm{ AlienSwarm{alienRow, alienColumn, gridSize, leftBoundary, rightBoundary, initialAlienSwarmSpeed, alienProjectiles} };
	const int enemyProjectileDamage = -1;

	void assignBomber();
	void manageVerticalBoundaries();
	void manageHorizontalBoundaries();
	void manageAlienCollisions();
	void manageHeroCollisions();
	void manageWinCondition();
	void manageLoseCondition();
;	bool isOnBoundary();
};
