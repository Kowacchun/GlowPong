//----------------------------------------------------------
//
// Name: Alan Cheng
// SID: 861094564
//
// CS 120B Final Project: GlowPong
//
// Filename: gamefunctions.c
//
//----------------------------------------------------------

#include <avr/io.h>
#include <stdlib.h>
#include "gamefunctions.h"
#include "utilities.h"

//external variables

extern volatile unsigned char counter;
extern volatile unsigned char winnerDecided;

unsigned char playerOne = 0x00;
unsigned char playerTwo = 0x00;

unsigned char currDisplay = 0x00;

extern unsigned char blinkCounter;

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

extern volatile signed char fireballTrajectory;

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
extern volatile signed char ballXPosition;
extern volatile signed char ballYPosition;

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
void reverseXTrajectory(signed char prevXTrajectory) {
	currXTrajectory = prevXTrajectory * -1;
}

// Reverses current Y trajectory
void reverseYTrajectory(signed char prevYTrajectory) {
	currYTrajectory = prevYTrajectory * -1;
}

// BALL FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void updateBallPosition(signed char currXTrajectory, signed char currYTrajectory) {
	ballXPosition = ballXPosition + currXTrajectory;
	ballYPosition = ballYPosition + currYTrajectory;
}

void ballCollisionHandler(signed char ballXPosition, signed char ballYPosition) {
	
	if(ballXPosition == 7 && currXTrajectory > 0) {
		reverseXTrajectory(currXTrajectory);
	}

	else if(ballXPosition == 0 && currXTrajectory < 0) {
		reverseXTrajectory(currXTrajectory);
	}
	
	else if(ballXPosition == 6 && currXTrajectory == 2) {
		changeXTrajectory(1);
	}
	
	else if(ballXPosition == 1 && currXTrajectory == -2) {
		changeXTrajectory(-1);
	}

	else if(ballYPosition == 6 && currYTrajectory > 0) {
		if(ballXPosition == playerOnePaddleLeft) {
			if(currXTrajectory == 0) {
				changeXTrajectory(-1);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(-2);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(-1);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(-2);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(-2);
				currYTrajectory = -1;
				lastTouch = 1;
			}
		}

		else if(ballXPosition == playerOnePaddleCenter) {
			if(currXTrajectory == 0) {
				changeXTrajectory(0);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(1);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(1);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(-1);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(-1);
				currYTrajectory = -1;
				lastTouch = 1;
			}
		}

		else if(ballXPosition == playerOnePaddleRight) {
			if(currXTrajectory == 0) {
				changeXTrajectory(1);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(2);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(2);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(1);
				currYTrajectory = -1;
				lastTouch = 1;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(2);
				currYTrajectory = -1;
				lastTouch = 1;
			}
		}
	}

	else if(ballYPosition == 1 && currYTrajectory < 0) {
		if(ballXPosition == playerTwoPaddleLeft) {
			if(currXTrajectory == 0) {
				changeXTrajectory(1);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(1);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(2);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(2);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(2);
				currYTrajectory = 1;
				lastTouch = 2;
			}
		}

		else if(ballXPosition == playerTwoPaddleCenter) {
			if(currXTrajectory == 0) {
				changeXTrajectory(0);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(1);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(1);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(-1);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(-1);
				currYTrajectory = 1;
				lastTouch = 2;
			}
		}

		else if(ballXPosition == playerTwoPaddleRight) {
			if(currXTrajectory == 0) {
				changeXTrajectory(-1);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == 1) {
				changeXTrajectory(-1);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == 2) {
				changeXTrajectory(-2);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == -1) {
				changeXTrajectory(-2);
				currYTrajectory = 1;
				lastTouch = 2;
			}

			else if(currXTrajectory == -2) {
				changeXTrajectory(-2);
				currYTrajectory = 1;
				lastTouch = 2;
			}
		}
	}

	else if(ballXPosition == 0 && ballYPosition == 6 && playerOnePaddleLeft == 0) {
		changeXTrajectory(1);
		currYTrajectory = -1;
		lastTouch = 1;
	}

	else if(ballXPosition == 0 && ballYPosition == 1 && playerTwoPaddleRight == 0) {
		changeXTrajectory(1);
		currYTrajectory = 1;
		lastTouch = 2;
	}

	else if(ballXPosition == 7 && ballYPosition == 6 && playerOnePaddleRight == 7) {
		changeXTrajectory(-1);
		currYTrajectory = -1;
		lastTouch = 1;
	}

	else if(ballXPosition == 7 && ballYPosition == 1 && playerTwoPaddleLeft == 7) {
		changeXTrajectory(-1);
		currYTrajectory = 1;
		lastTouch = 2;
	}
	
	else if(ballYPosition > 7) {
		playerTwoScore = playerTwoScore + 1;
		softResetGame();
	}
	
	else if(ballYPosition < 0) {
		playerOneScore = playerOneScore + 1;
		softResetGame();
	}

	//----------------NEED TO DECLARE FIRE BALL COLLISIONS UNDER HERE --------------------------
	
	else if(ballYPosition == fireballYPosition && ballXPosition == fireballXPosition && fireballOn == 1) {
		if(lastTouch == 1) {
			playerTwoScore = playerTwoScore + 1;
			softResetGame();
		}
		
		else if(lastTouch == 2) {
			playerOneScore = playerOneScore + 1;
			softResetGame();
		}
	}

}

// SPECIAL MODE FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void updateFireballPosition() {
	fireballXPosition = fireballXPosition + fireballTrajectory;
}

void fireballCollisionHandler() {
	if(fireballXPosition == 0 && fireballTrajectory == -1) {
		fireballTrajectory = 1;
	}
	
	if(fireballXPosition == 7 && fireballTrajectory == 1) {
		fireballTrajectory = -1;
	}
}

void mirrorCollisionHandler() {
	
	if(ballYPosition == mirrorLocation) {
		reverseXTrajectory(currXTrajectory);
	}
}

// END GAME FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays scores constantly for two players.
// AI also counts as player 2
void displayScores() {
	
	if(playerOneScore == 1) {
		playerOne = SetBit(0, 0, 1);
	}
	
	if(playerTwoScore == 1) {
		playerTwo = SetBit(0, 3, 1);
	}
	
	if(playerOneScore == 2) {
		playerOne = SetBit(0, 0, 1);
		playerOne = SetBit(playerOne, 1, 1);
	}
	
	if(playerTwoScore == 2) {
		playerTwo = SetBit(0, 3, 1);
		playerTwo = SetBit(playerTwo, 4, 1);
	}	
	
	if(playerOneScore == 3) {
		playerOne = SetBit(0, 0, 1);
		playerOne = SetBit(playerOne, 1, 1);
		playerOne = SetBit(playerOne, 2, 1);
		winnerDecided = 1;
	}
	
	if(playerTwoScore == 3) {
		playerTwo = SetBit(0, 3, 1);
		playerTwo = SetBit(playerTwo, 4, 1);
		playerTwo = SetBit(playerTwo, 5, 1);
		winnerDecided = 1;
	}
	
	PORTC = playerOne | playerTwo;
}

// Blinks the LED for the winning player's score LEDs
// Requires 2 LEDs
void blinkWinnerLED(unsigned char playerOneStatus, unsigned char playerTwoStatus) {
	
	unsigned char blinker = 0x00;
	unsigned char nonBlinker = 0x00;
	
	if(playerOneScore == 3) {
		blinker = playerOneStatus;
		nonBlinker = playerTwoStatus;
	} 
	
	if(playerTwoScore == 3) {
		blinker = playerTwoStatus;
		nonBlinker = playerOneStatus;
	}
	
	if(blinkCounter == 1) {
		currDisplay = 0x00 | nonBlinker;
	}
	
	if(blinkCounter != 30 && blinkCounter % 10 == 0) {
		currDisplay = blinker | nonBlinker;
	}
	
	if(blinkCounter % 20 == 0) {
		currDisplay = 0x00 | nonBlinker;
	}
	
	if(blinkCounter == 30) {
		blinkCounter = 1;
		hardResetGame();
	}
	
	PORTC = currDisplay;
	
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
	
	fireballXPosition = 0;
	fireballYPosition = 4;

	fireballTrajectory = 1;
}

//hard resets the game (resets everything)
void hardResetGame() {
	winnerDecided = 0;
	playerOne = 0x00;
	playerTwo = 0x00;
	
	currDisplay = 0x00;
	
	// Define settings and mechanics
	currMode = 1;
	numPlayers = 1;
	currXTrajectory = 0;
	currYTrajectory = 1;

	playerOneScore = 0;
	playerTwoScore = 0;

	// Flag that tells you if the game is running (when on, it does not let you change settings anymore)
	gameLoaded = 0;

	// Who touched the ball last - player 1 is 1, player 2 is 2
	lastTouch = 1;

	// Special mode objects ---------------------------------
	// Fireball
	fireballXPosition = 0;
	fireballYPosition = 4;

	fireballTrajectory = 1;

	// Fireball Flag
	fireballOn = 0;

	//-----------------------------------

	// Mirror only has Y axis placement
	mirrorLocation = 4;

	// Mirror Flag
	mirrorOn = 0;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Player 1 Paddle
	// These are the bit positions (NOT the actual values)
	// Moving right will increase the values
	// Moving left will decrease the values
	playerOnePaddleLeft = 2;
	playerOnePaddleCenter = 3;
	playerOnePaddleRight = 4;

	playerOnePaddleVertical = 7;

	// Player 2 Paddle
	// These are the bit positions (NOT the actual values)
	// Moving right will decrease the values
	// Moving left will increase the values
	playerTwoPaddleLeft = 4;
	playerTwoPaddleCenter = 3;
	playerTwoPaddleRight = 2;

	playerTwoPaddleVertical = 0;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Ball position
	ballXPosition = 3;
	ballYPosition = 4;
}

// Runs the game with the settings set by player 1
void runGame(unsigned char currMode, unsigned char numPlayers) {
	if(counter == 10 && winnerDecided != 1) {
		updateBallPosition(currXTrajectory, currYTrajectory);
		updateFireballPosition();
		counter = 0;
		
		if(mirrorOn == 1) {
			mirrorCollisionHandler(currXTrajectory);
		}
	}
	
	ballCollisionHandler(ballXPosition, ballYPosition);
	fireballCollisionHandler();
	
	if(numPlayers == 1) {
		ComputerAI();
	}
	
	displayScores();
	
	if(playerOneScore == 3 || playerTwoScore == 3) {
		blinkWinnerLED(playerOne, playerTwo);
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

	if(followChance < 5) {
		if(ballXPosition < playerTwoPaddleRight) {
			playerTwoRightPaddleMove();
		}

		else if(ballXPosition > playerTwoPaddleLeft) {
			playerTwoLeftPaddleMove();
		}
	}
}