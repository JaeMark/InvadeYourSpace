#pragma once

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
	enum class GameState { startScreen, playing, won, lost };
	GameState gameState{ GameState::startScreen }; // default game state

	ofTrueTypeFont title;
	ofTrueTypeFont instructionsTitle;
	ofTrueTypeFont instructions;
	const std::string titleStr{ "INVADE YOUR SPACE" };
	const std::string instructionsTitleStr{ "INSTRUCTIONS" };
	const std::string instructionsStr {
		"CONTROLS:   Press A or Move Mouse to the Left to Move Left\n"
		"\t\t\t\t\t\t Press D or Move Mouse to the Right to Move Right\n"
		"\t\t\t\t\t\t Press W or Press Mouse to a Fire Projectile\n"
		"SCORE:\t\t   10 points for each alien in the bottom two rows\n"
		"\t\t\t\t\t\t20 points for each alien in the next two rows up\n"
		"\t\t\t\t\t\t30 points for each alien in the top row\n"
		"VICTORY:\t  Destroy All Alien Ships.\n"
		"GAME OVER: The Alien Swarm Has Reached the Player\n"
		"\t\t\t\t\t\tThe Player Ship is Damaged 3 Times\n" };

	ofTrueTypeFont startFont;
	ofRectangle startButton;
	ofColor startButtonColor{ofColor::white};
	const std::string startStr{ "START" };
	bool isButtonHovered = false;

	ofTrueTypeFont gameResult;
	const std::string victoryStr{ "Mission Complete!" };
	const std::string gameOverStr{ "Mission Failed!" };

	const float lineHeight{ 34.0 };
	const float letterSpacing{ 1.035 };

	ofSoundPlayer introAudio;
	ofSoundPlayer gameStartAudio;
	ofSoundPlayer backgroundAudio;
	ofSoundPlayer victoryAudio;
	ofSoundPlayer gameOverAudio;
	bool isVictoryAudioPlayed = false;
	bool isGameOverAudioPlayed = false;

	const int leftBoundary{ 100 };
	const int rightBoundary{ ofGetWidth() - 100 };
	const int upperBoundary{ 100 };
	const int lowerBoundary{ ofGetHeight() - 100 };


	std::string playerAvatarStr{ "Assets/playerShip.png" };
	const double heroCoordinateY{ lowerBoundary - 50.0 };
	Coordinate heroCoordinate{ static_cast<double>(ofGetWidth() / 2), heroCoordinateY };
	Health heroHealth{ 3, Coordinate{static_cast<double>(ofGetWidth()) - 210, (static_cast<double>(ofGetHeight()) + lowerBoundary) / 2} };
	Score heroScore{ 0 , Coordinate{30, (static_cast<double>(ofGetHeight()) + lowerBoundary) / 2}};
	std::vector<Projectile> heroProjectiles;
	Player player{ Player{ playerAvatarStr, heroCoordinate, heroHealth, heroScore, heroProjectiles}};
	const int heroMovementSpeed{ 20 };

	const int alienRow{ 5 };
	const int alienColumn{ 11 };
	const int gridSize = 50;
	Coordinate initialAlienSwarmSpeed{ 2, 10 };
	std::vector<Projectile> alienProjectiles;
	AlienSwarm alienSwarm{ AlienSwarm{alienRow, alienColumn, gridSize, leftBoundary, rightBoundary, initialAlienSwarmSpeed, alienProjectiles} };
	const float attackProbability{ 0.01 }; // probability of an alien to attack each frame
	const int enemyProjectileDamage{ -1 };
	
	void drawInstruction() const;
	void drawStartButton() const;
	void drawEndScreen() const;
	void cleanUpProjectiles();
	void manageAlienCollisions();
	void manageHeroCollisions();
	void manageWinCondition();
	void manageLoseCondition();
};
