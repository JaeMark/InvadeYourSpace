#pragma once

#include "Alien.h"
#include "ofMain.h"
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
	Score heroScore{ 0 };
	const int heroMovementSpeed = 10;
	std::vector<Projectile> heroProjectiles;


	const int alienRow{ 5 };
	const int alienColumn{ 11 };
	const int gridSize = 50;
	std::vector<vector<Alien>> alienSwarm;
	std::vector<int> alienBomberRow; // available bombers
	Projectile alienProjectile{{0, 0}, Projectile::Type::enemy };
	bool isBomberAssigned = false;

	Coordinate alienSwarmSpeed{ 1, 5 };

	void assignBomber();
	void checkVerticleBoundaries();
	void checkHorizontalBoundaries();
	void checkCollisions();
	bool isOnBoundary();
};
