#ifndef __GAMEFUNCTIONS_H__
#define __GAMEFUNCTIONS_H__


// SETTING FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Cycles between one player (0x01) and two players (0x03)
// Requires 2 LEDs
// Requires 1 Button
void chooseNumPlayers(unsigned char newNumPlayers);

// Cycles between Normal (0x01) / Fireball (0x02) / Invert (0x03) Barrier modes
// Requires 2 LEDs
// Requires 1 Button
void changeMode(unsigned char newMode);

// TRAJECTORY FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Changes X trajectory factor ... ex) 1 -> 2 or -1 -> -2 or 2 -> 1 or -2 -> -1
void changeXTrajectory(signed char newXTrajectory);

// Reverses current X trajectory
void reverseXTrajectory(signed char prevXTrajectory);

// Reverses current Y trajectory
void reverseYTrajectory(signed char prevYTrajectory);

// BALL FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void updateBallPosition(signed char currXTrajectory, signed char currYTrajectory);

void ballCollisionHandler(unsigned char ballXPosition, unsigned char ballYPosition);

// SPECIAL MODE FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void updateFireballPosition(unsigned char fireballXPosition);

void fireballCollisionHandler(unsigned char fireballXPosition);

void mirrorCollisionHandler(signed char currXTrajectory, signed char currYTrajectory);

// END GAME FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays scores constantly for two players.
// AI also counts as player 2
void displayScores(unsigned char playerOneScore, unsigned char playerTwoScore);

// Blinks the LED for the winning player's score LEDs
// Requires 2 LEDs
void blinkWinnerLED(unsigned char playerOneScore, unsigned char playerTwoScore);

// GEMU FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Soft resets the game (paddle position and etc)
void softResetGame();

//hard resets the game (resets everything)
void hardResetGame();

// Runs the game with the settings set by player 1
void runGame(unsigned char currMode, unsigned char numPlayers);


// PADDLE MOVEMENT FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void playerOneLeftPaddleMove();

void playerTwoLeftPaddleMove();

void playerOneRightPaddleMove();

void playerTwoRightPaddleMove();

// AI MOVEMENT CODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ComputerAI();

#endif