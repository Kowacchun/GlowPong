#include <avr/io.h>
#include <stdlib.h>
#include "gamefunctions.h"

//external variables

unsigned char counter;

// Define settings and mechanics
extern volatile unsigned char currMode;
extern volatile unsigned char numPlayers;
extern volatile signed char currXTrajectory;
extern volatile signed char currYTrajectory;

extern volatile unsigned char playerOneScore;
extern volatile unsigned char playerTwoScore;
extern volatile unsigned char computerAIScore;

// Flag that tells you if the game is running (when on, it does not let you change settings anymore)
extern volatile unsigned char gameLoaded;

// Who touched the ball last - player 1 is 1, player 2 is 2
extern volatile unsigned char lastTouch;

// Special mode objects ---------------------------------
// Fireball
extern volatile unsigned char fireballXPosition;
extern volatile unsigned char fireballYPosition;

extern volatile unsigned char fireballTrajectory;

// Fireball Flag
extern volatile unsigned char fireballOn;

//-----------------------------------

// Mirror only has Y axis placement
extern volatile unsigned char mirrorLocation;

// Mirror Flag
extern volatile unsigned char mirrorOn;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Player 1 Paddle
// These are the bit positions (NOT the actual values)
// Moving right will increase the values
// Moving left will decrease the values
extern volatile unsigned char playerOnePaddleLeft;
extern volatile unsigned char playerOnePaddleCenter;
extern volatile unsigned char playerOnePaddleRight;

extern volatile unsigned char playerOnePaddleVertical;

// Player 2 Paddle
// These are the bit positions (NOT the actual values)
// Moving right will decrease the values
// Moving left will increase the values
extern volatile unsigned char playerTwoPaddleLeft;
extern volatile unsigned char playerTwoPaddleCenter;
extern volatile unsigned char playerTwoPaddleRight;

extern volatile unsigned char playerTwoPaddleVertical;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Ball position
extern volatile unsigned char ballXPosition;
extern volatile unsigned char ballYPosition;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SETTING FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

// TRAJECTORY FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Changes X trajectory factor ... ex) 1 -> 2 or -1 -> -2 or 2 -> 1 or -2 -> -1
void changeXTrajectory(signed char newXTrajectory) {
	currXTrajectory = newXTrajectory;
}

// Reverses current X trajectory
void reverseXTrajectory(signed char currXTrajectory) {
	currXTrajectory = currXTrajectory * -1;
}

// Reverses current Y trajectory
void reverseYTrajectory(signed char currYTrajectory) {
	currYTrajectory = currYTrajectory * -1;
}

// BALL FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void updateBallPosition(signed char currXTrajectory, signed char currYTrajectory) {
	ballXPosition = ballXPosition + currXTrajectory;
	ballYPosition = ballYPosition + currYTrajectory;
}

void ballCollisionHandler(signed char currXTrajectory, signed char currYTrajectory, unsigned char ballXPosition, unsigned char ballYPosition) {
	if(ballXPosition == 7 && currXTrajectory > 0) {
		reverseXTrajectory(currXTrajectory);
	}

	if(ballXPosition == 0 && currXTrajectory < 0) {
		reverseXTrajectory(currXTrajectory);
	}

	if(ballYPosition == 6 && currYTrajectory > 0) {
		if(ballXPosition == playerOnePaddleLeft) {
			if(currXTrajectory == 0) {
				changeXTrajectory(-1);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(-2);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(-1);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(-2);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(-2);
				currYTrajectory = -1;
			}
		}

		else if(ballXPosition == playerOnePaddleCenter) {
			if(currXTrajectory == 0) {
				changeXTrajectory(0);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(1);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(1);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(-1);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(-1);
				currYTrajectory = -1;
			}
		}

		else if(ballXPosition == playerOnePaddleRight) {
			if(currXTrajectory == 0) {
				changeXTrajectory(1);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(2);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(2);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(1);
				currYTrajectory = -1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(2);
				currYTrajectory = -1;
			}
		}
	}

	if(ballYPosition == 1 && currYTrajectory < 0) {
		if(ballXPosition == playerTwoPaddleLeft) {
			if(currXTrajectory == 0) {
				changeXTrajectory(1);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(1);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(2);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(2);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(2);
				currYTrajectory = 1;
			}
		}

		else if(ballXPosition == playerTwoPaddleCenter) {
			if(currXTrajectory == 0) {
				changeXTrajectory(0);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(1);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(1);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(-1);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(-1);
				currYTrajectory = 1;
			}
		}

		else if(ballXPosition == playerTwoPaddleRight) {
			if(currXTrajectory == 0) {
				changeXTrajectory(-1);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(-1);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(-2);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(-2);
				currYTrajectory = 1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(-2);
				currYTrajectory = 1;
			}
		}
	}

	if(ballXPosition == 0 && ballYPosition == 6 && playerOnePaddleLeft == 0) {
		changeXTrajectory(1);
		currYTrajectory = -1;
	}

	if(ballXPosition == 0 && ballYPosition == 1 && playerTwoPaddleRight == 0) {
		changeXTrajectory(1);
		currYTrajectory = 1;
	}

	if(ballXPosition == 7 && ballYPosition == 6 && playerOnePaddleRight == 7) {
		changeXTrajectory(-1);
		currYTrajectory = -1;
	}

	if(ballXPosition == 7 && ballYPosition == 1 && playerTwoPaddleLeft == 7) {
		changeXTrajectory(-1);
		currYTrajectory = 1;
	}
	
	if(ballYPosition > 7) {
		playerTwoScore = playerTwoScore + 1;
		softResetGame();
	}
	
	if(ballYPosition < 0) {
		playerOneScore = playerOneScore + 1;
		softResetGame();
	}

	//----------------NEED TO DECLARE FIRE BALL COLLISIONS UNDER HERE --------------------------



}

// SPECIAL MODE FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void updateFireballPosition(unsigned char fireballXPosition) {

}

void fireballCollisionHandler(unsigned char fireballXPosition) {

}

void mirrorCollisionHandler(signed char currXTrajectory, signed char currYTrajectory) {

}

// END GAME FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays scores constantly for two players.
// AI also counts as player 2
void displayScores(unsigned char playerOneScore, unsigned char playerTwoScore) {

}

// Blinks the LED for the winning player's score LEDs
// Requires 2 LEDs
void blinkWinnerLED(unsigned char playerOneScore, unsigned char playerTwoScore) {

}

// GEMU FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Soft resets the game (paddle position and etc)
void softResetGame() {
	
	//Reset player one
	playerOnePaddleLeft = 2;
	playerOnePaddleCenter = 3;
	playerOnePaddleRight = 4;

	playerOnePaddleVertical = 7;
	
	// Reset player two
	playerTwoPaddleLeft = 4;
	playerTwoPaddleCenter = 3;
	playerTwoPaddleRight = 2;

	playerTwoPaddleVertical = 0;
	
	// Reset ball position
	ballXPosition = 3;
	ballYPosition = 4;
	
	// Reset trajectories
	currXTrajectory = 0;
	currYTrajectory = 1;
}

//hard resets the game (resets everything)
void hardResetGame() {

}

// Runs the game with the settings set by player 1
void runGame(unsigned char currMode, unsigned char numPlayers) {
	if(counter == 10) {
		updateBallPosition(currXTrajectory, currYTrajectory);
		counter = 0;
	}
	ballCollisionHandler(currXTrajectory, currYTrajectory, ballXPosition, ballYPosition);

	if(numPlayers == 1) {
		ComputerAI();
	}
}


// PADDLE MOVEMENT FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void playerOneLeftPaddleMove() {
	if(playerOnePaddleLeft != 0) {
		playerOnePaddleLeft = playerOnePaddleLeft - 1;
		playerOnePaddleCenter = playerOnePaddleCenter - 1;
		playerOnePaddleRight = playerOnePaddleRight - 1;
	}
}

void playerTwoLeftPaddleMove() {
	if(playerTwoPaddleLeft != 7) {
		playerTwoPaddleLeft = playerTwoPaddleLeft + 1;
		playerTwoPaddleCenter = playerTwoPaddleCenter + 1;
		playerTwoPaddleRight = playerTwoPaddleRight + 1;
	}
}

void playerOneRightPaddleMove() {
	if(playerOnePaddleRight != 7) {
		playerOnePaddleLeft = playerOnePaddleLeft + 1;
		playerOnePaddleCenter = playerOnePaddleCenter + 1;
		playerOnePaddleRight = playerOnePaddleRight + 1;
	}
}

void playerTwoRightPaddleMove() {
	if(playerTwoPaddleRight != 0) {
		playerTwoPaddleLeft = playerTwoPaddleLeft - 1;
		playerTwoPaddleCenter = playerTwoPaddleCenter - 1;
		playerTwoPaddleRight = playerTwoPaddleRight - 1;
	}
}

// AI MOVEMENT CODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ComputerAI() {
	unsigned char followChance = rand() % 100;

	if(followChance == 1) {
		if(ballXPosition < playerTwoPaddleRight) {
			playerTwoRightPaddleMove();
		}

		else if(ballXPosition > playerTwoPaddleLeft) {
			playerTwoLeftPaddleMove();
		}
	}
}