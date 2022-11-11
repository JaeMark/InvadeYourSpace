#pragma once
#include "Alien.h"

class AlienSwarm {
	std::vector<std::vector<Alien>> myAlienSwarm;
	std::vector<std::vector<bool>> myAlienSwarmGrid; // pseudo pointer
	int mySwarmRow;
	int mySwarmColumn;
	Coordinate mySpeed;
public:
	AlienSwarm(const std::vector<std::vector<Alien>>& alienSwarm, const int& row, const int& column, const Coordinate& speed)
		: myAlienSwarm{ alienSwarm }, mySwarmRow{ row }, mySwarmColumn{ column }, mySpeed{ speed }
	{
		fillGrid();
	}

	void draw() {
		for (int n{ 0 }; n < mySwarmRow; n++) {
			for (int m{ 0 }; m < mySwarmColumn; m++) {
				if (myAlienSwarmGrid[n][m]) {
					myAlienSwarm[n][m].draw();
				}
			}
		}
	}

	void moveSwarm(const int& leftBoundary, const int& rightBoundary) {
		// check if the alien swarm has reached the edge
		bool moveDown = false;
		for (auto const alienRow : myAlienSwarm) {
			for (auto const alien : alienRow) {
				if (alien.isOnBoundary(leftBoundary, rightBoundary)) {
					moveDown = true;
					mySpeed.x *= -1;
					break;
				}
			}
		}
		// move the alien swarm
		for (auto& alienRow : myAlienSwarm) {
			for (auto& alien : alienRow) {
				if (moveDown) {
					alien.update({ mySpeed.x , mySpeed.y });
				}
				else {
					alien.update({ mySpeed.x , 0 });
				}
			}
		}
	}

	void destroyAlien(int row, int column) {
		myAlienSwarmGrid[row][column] = false;
	}

	ofRectangle getAlienCollision(int row, int column) {
		return myAlienSwarm[row][column].collision;
	}

	int getAlienValue(int row, int column) {
		return myAlienSwarm[row][column].value();
	}

private:
	void fillGrid() {
		std::vector <bool> swarmRow;
		for (int n{ 0 }; n < mySwarmRow; n++) {
			for (int m{ 0 }; m < mySwarmColumn; m++) {
				swarmRow.push_back(true);
			}
			myAlienSwarmGrid.push_back(swarmRow);
		}
	}
};
