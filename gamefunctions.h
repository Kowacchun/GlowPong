#ifndef __GAMEFUNCTIONS_H__
#define __GAMEFUNCTIONS_H__


// Cycles between one player (0x01) and two players (0x03)
// Requires 2 LEDs
// Requires 1 Button
void chooseNumPlayers(unsigned char numPlayers);

// Cycles between Normal (0x01) / Fireball (0x02) / Invert (0x03) Barrier modes
// Requires 2 LEDs
// Requires 1 Button
void changeMode(unsigned char currMode);

// TRAJECTORY FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Passes in both trajectories, but only modifies X trajectory maxing out at 2. 
// Note: X and Y make the slope
void changeTrajectory(unsigned char currXTrajectory, unsigned char currYTrajectory);

void reverseTrajectory(unsigned char currXTrajectory, unsigned char currYTrajectory);

void collisionHandler(unsigned currXTrajectory, unsigned char currYTrajectory);

// BALL FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void updateBallPosition(unsigned currXTrajectory, unsigned char currYTrajectory);

// END GAME FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays scores constantly for two players.
// AI also counts as player 2
void displayScores(unsigned char playerOneScore, unsigned char playerTwoScore);

// Blinks the LED for the winning player's score LEDs
// Requires 2 LEDs
void blinkWinnerLED(unsigned char playerOneScore, unsigned char playerTwoScore);

// Soft resets the game
void resetGame();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Runs the game with the settings set by player 1
void runGame(unsigned char currMode, unsigned char numPlayers);


// PADDLE MOVEMENT FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void leftPaddleMove();

void rightPaddleMove();

#endif