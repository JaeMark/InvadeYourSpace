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
	const int upperBoundary = 100;
	const int lowerBoundary = ofGetHeight() - 100;

	const double heroCoordinateY = lowerBoundary - 50;
	const double heroScoreCoordinateY = upperBoundary - 50;
	Coordinate heroCoordinate{ static_cast<double>(ofGetWidth() / 2), heroCoordinateY };
	Score heroScore{ 0 , Coordinate{30, (static_cast<double>(ofGetHeight()) + lowerBoundary) / 2}};
	Health heroHealth{ 3, Coordinate{230, (static_cast<double>(ofGetHeight()) + lowerBoundary) / 2} };
	std::vector<Projectile> heroProjectiles;
	Player player{ Player{ "Assets/playerShip.png", heroCoordinate, heroHealth, heroScore, heroProjectiles}};
	const int heroMovementSpeed = 20;

	const int alienRow{ 5 };
	const int alienColumn{ 11 };
	const int gridSize = 50;
	Coordinate initialAlienSwarmSpeed{ 2, 10 };
	std::vector<Projectile> alienProjectiles;
	AlienSwarm alienSwarm{ AlienSwarm{alienRow, alienColumn, gridSize, leftBoundary, rightBoundary, initialAlienSwarmSpeed, alienProjectiles} };
	const float attackProbability = 0.01; // probability of an alien to attack each frame
	const int enemyProjectileDamage = -1;

	ofTrueTypeFont title;
	
	void cleanUpProjectiles();
	void manageAlienCollisions();
	void manageHeroCollisions();
	void manageWinCondition() const;
	void manageLoseCondition() const;
};
