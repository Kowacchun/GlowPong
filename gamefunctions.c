#include <avr/io.h>
#include "gamefunctions.h"

// Cycles between one player (0x01) and two players (0x03)
// Requires 2 LEDs
// Requires 1 Button
void chooseNumPlayers(unsigned char newNumPlayers) {
	numPlayers = newNumPlayers;
}

// Cycles between Normal (0x01) / Fireball (0x02) / Invert (0x03) Barrier modes
// Requires 2 LEDs
// Requires 1 Button
void changeMode(unsigned char newMode) {
	currMode = newMode;
}


//FUNCTIONS REGARDING TRAJECTORY ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Passes in both trajectories, but only modifies X trajectory maxing out at 2. 
// Note: X and Y make the slope
void changeTrajectory(unsigned char currXTrajectory, unsigned char currYTrajectory) {

}

void reverseTrajectory() {
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Displays scores constantly.
void displayScores(unsigned char playerOneScore, unsigned char playerTwoScore) {

}

// Blinks the LED for the winning player's score LEDs
// Requires 2 LEDs
void blinkWinnerLED(unsigned char playerOneScore, unsigned char playerTwoScore) {

}

// Soft resets the game and set everything back to default
void resetGame() {
	currMode = 1;
	numPlayers = 1;
	currXTrajectory = 1;
	currYTrajectory = 1;

	playerOneScore = 0;
	playerTwoScore = 0;
	computerAIScore = 0;

	gameLoaded = 0;

	playerOnePaddleLeft = 2;
	playerOnePaddleCenter = 3;
	playerOnePaddleRight = 4;

	playerTwoPaddleLeft = 4;
	playerTwoPaddleCenter = 3;
	playerTwoPaddleRight = 2;

	tasksNum = 3;
	gamePeriodGCD = 100;
	gamePeriod = 100;

	totalMatches = 5;
}

// Runs the game with the settings set by player 1
void runGame(unsigned char currMode, unsigned char numPlayers) {

}

// PADDLE MOVEMENT FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Updates paddle location accordingly
void leftPaddleMove();

void rightPaddleMove();