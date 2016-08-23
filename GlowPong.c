#include "avr/io.h"
#include "utilities.h"
#include "io.h"
#include "timer.h"
#include "scheduler.h"

#include "gamefunctions.h"

extern volatile unsigned char TimerFlag;

// MANY VARIABLE DECLARATIONS INCOMING!

// Define settings and mechanics
unsigned char currMode = 1;
unsigned char numPlayers = 1;
unsigned char currXTrajectory = 0;
unsigned char currYTrajectory = 1;

unsigned char playerOneScore = 0;
unsigned char playerTwoScore = 0;
unsigned char computerAIScore = 0;

// Flag that tells you if the game is running (when on, it does not let you change settings anymore)
unsigned char gameLoaded = 0;

// Who touched the ball last - player 1 is 1, player 2 is 2
unsigned char lastTouch = 1;

// Special mode objects ---------------------------------
// Fireball
unsigned char fireballXPosition = 0;
unsigned char fireballYPosition = 4;

unsigned char fireballTrajectory = 1;

// Fireball Flag
unsigned char fireballOn = 0;

//-----------------------------------

// Mirror only has Y axis placement
unsigned char mirrorLocation = 4;

// Mirror Flag
unsigned char mirrorOn = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Player 1 Paddle
// These are the bit positions (NOT the actual values)
// Moving right will increase the values
// Moving left will decrease the values
unsigned char playerOnePaddleLeft = 2;
unsigned char playerOnePaddleCenter = 3;
unsigned char playerOnePaddleRight = 4;

unsigned char playerOnePaddleVertical = 7;

// Player 2 Paddle
// These are the bit positions (NOT the actual values)
// Moving right will decrease the values
// Moving left will increase the values
unsigned char playerTwoPaddleLeft = 4;
unsigned char playerTwoPaddleCenter = 3;
unsigned char playerTwoPaddleRight = 2;

unsigned char playerTwoPaddleVertical = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Ball position
unsigned char ballXPosition = 3;
unsigned char ballYPosition = 6;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Define tasks period here
const unsigned char tasksNum = 5;
const unsigned char gamePeriodGCD = 30;
const unsigned char gamePeriod = 30;

// Constant number of total matches
const unsigned char totalMatches = 5;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Task array
task tasks[tasksNum];

// Output variables
unsigned char PS_B;
unsigned char MS_B;
unsigned char OutB;

// Define states for each function
enum PS_States {PS_Start, PS_OnePlayer, PS_OnePlayerRelease, PS_TwoPlayer, PS_TwoPlayerRelease};
int TickFct_PlayerSelection(int state);

enum MS_States {MS_Start, MS_Normal, MS_NormalRelease, MS_Fireball, MS_FireballRelease, MS_Invert, MS_InvertRelease};
int TickFct_ModeSelection(int state);

enum GS_States {GS_Start, GS_Setup, GS_RunGame};
int TickFct_GameStart(int state);

enum PDO_States {PDO_Start, PDO_Left, PDO_Right, PDO_Stationary};
int TickFct_PaddleMoveOne(int state);

enum PDT_States {PDT_Start, PDT_Left, PDT_Right, PDT_Stationary};
int TickFct_PaddleMoveTwo(int state);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Player Selection SM
int TickFct_PlayerSelection(int state) {
	switch(state) {
		case PS_Start:
		state = PS_OnePlayerRelease;
		break;

		case PS_OnePlayer:
		if(GetBit(PINA, 0) == 1 && gameLoaded != 1) {
			state = PS_OnePlayerRelease;
		}

		else {
			state = PS_OnePlayer;
		}

		break;

		case PS_OnePlayerRelease:
		if(GetBit(PINA, 0) == 0 && gameLoaded != 1) {
			state = PS_TwoPlayer;
		}

		else {
			state = PS_OnePlayerRelease;
		}

		break;

		case PS_TwoPlayer:
		if(GetBit(PINA, 0) == 1 && gameLoaded != 1) {
			state = PS_TwoPlayerRelease;
		}

		else {
			state = PS_TwoPlayer;
		}

		break;

		case PS_TwoPlayerRelease:
		if(GetBit(PINA, 0) == 0 && gameLoaded != 1) {
			state = PS_OnePlayer;
		}

		else {
			state = PS_TwoPlayerRelease;
		}

		break;

		default:
		state = PS_Start;
		break;
	}

	switch(state) {
		case PS_Start:
		;
		break;

		case PS_OnePlayer:
		PS_B = SetBit(0, 0, 1);
		chooseNumPlayers(1);
		break;

		case PS_OnePlayerRelease:
		PS_B = SetBit(0, 0, 1);
		chooseNumPlayers(1);
		break;

		case PS_TwoPlayer:
		PS_B = SetBit(0, 1, 1);
		chooseNumPlayers(2);
		break;

		case PS_TwoPlayerRelease:
		PS_B = SetBit(0, 1, 1);
		chooseNumPlayers(2);
		break;

		default:
		chooseNumPlayers(1);
		break;
	}

	return state;
}

// Mode Selection SM
int TickFct_ModeSelection(int state) {
	switch(state) {
		case MS_Start:
		state = MS_NormalRelease;
		break;

		case MS_Normal:
		if(GetBit(PINA, 1) == 0 && gameLoaded != 1) {
			state = MS_NormalRelease;
		}
		
		else {
			state = MS_Normal;
		}
		
		break;

		case MS_NormalRelease:
		if(GetBit(PINA, 1) == 1 && gameLoaded != 1) {
			state = MS_Fireball;
		}
			
		else {
			state = MS_NormalRelease;
		}	

		break;

		case MS_Fireball:
		if(GetBit(PINA, 1) == 0 && gameLoaded != 1) {
			state = MS_FireballRelease;
		}
		
		else {
			state = MS_Fireball;
		}
		
		break;

		case MS_FireballRelease:
		if(GetBit(PINA, 1) == 1 && gameLoaded != 1) {
			state = MS_Invert;
		}
		
		else {
			state = MS_FireballRelease;
		}
		
		break;

		case MS_Invert:
		if(GetBit(PINA, 1) == 0 && gameLoaded != 1) {
			state = MS_InvertRelease;	
		}
		
		else {
			state = MS_Invert;
		}
		
		break;

		case MS_InvertRelease:
		if(GetBit(PINA, 1) == 1 && gameLoaded != 1) {
			state = MS_Normal;
		}
		
		else {
			state = MS_InvertRelease;
		}
		
		break;

		default:
		state = MS_Start;
		break;
	}

	switch(state) {
		case MS_Start:
		;
		break;

		case MS_Normal:
		MS_B = SetBit(0, 2, 1);
		changeMode(1);
		break;

		case MS_NormalRelease:
		MS_B = SetBit(0, 2, 1);
		changeMode(1);
		break;

		case MS_Fireball:
		MS_B = SetBit(0, 3, 1);
		changeMode(2);
		break;

		case MS_FireballRelease:
		MS_B = SetBit(0, 3, 1);
		changeMode(2);
		break;

		case MS_Invert:
		MS_B = SetBit(0, 2, 1);
		MS_B = SetBit(MS_B, 3, 1);
		changeMode(3);
		break;

		case MS_InvertRelease:
		MS_B = SetBit(0, 2, 1);
		MS_B = SetBit(MS_B, 3, 1);
		changeMode(3);
		break;

		default:
		changeMode(1);
		break;
	}
	
	return state;
}

// Game Start SM
int TickFct_GameStart(int state) {
	switch(state) {
		case GS_Start:
		state = GS_Setup;
		break;

		case GS_Setup:
		if(GetBit(PINA, 2) == 1) {
			state = GS_RunGame;
		}

		else {
			state = GS_Setup;
		}

		break;

		case GS_RunGame:
		if(gameLoaded == 1) {
			state = GS_RunGame;
		}

		else {
			state = GS_Start;
		}

		break;

		default:
		state = GS_Start;
		break;
	}

	switch(state) {
		case GS_Start:
		;
		break;

		case GS_Setup:
		;
		break;

		case GS_RunGame:
		runGame(currMode, numPlayers);
		break;

		default:
		;
		break;
	}
}

int TickFct_PaddleMoveOne(int state) {
	switch(state) {
		case PDO_Start:
		state = PDO_Stationary;
		break;

		case PDO_Stationary:
		if(GetBit(PINA, 3) == 1) {
			state = PDO_Right;
		}

		else if(GetBit(PINA, 4) == 1) {
			state = PDO_Left;
		}

		else {
			state = PDO_Stationary;
		}

		break;

		case PDO_Left:
		state = PDO_Stationary;
		break;

		case PDO_Right:
		state = PDO_Stationary;
		break;

		default:
		state = PDO_Start;
		break;
	}

	switch(state) {
		case PDO_Start:
		;
		break;

		case PDO_Stationary:
		;
		break;

		case PDO_Left:
		playerOneLeftPaddleMove();
		break;

		case PDO_Right:
		playerOneRightPaddleMove();
		break;

		default:
		;
		break;
	}
}

int TickFct_PaddleMoveTwo(int state) {
	switch(state) {
		case PDT_Start:
		state = PDT_Stationary;
		break;

		case PDT_Stationary:
		if(GetBit(PINA, 5) == 1) {
			state = PDT_Right;
		}

		else if(GetBit(PINA, 6) == 1) {
			state = PDT_Left;
		}

		else {
			state = PDT_Stationary;
		}

		break;

		case PDT_Left:
		state = PDT_Stationary;
		break;

		case PDT_Right:
		state = PDT_Stationary;
		break;

		default:
		state = PDT_Start;
		break;
	}

	switch(state) {
		case PDT_Start:
		;
		break;

		case PDT_Stationary:
		;
		break;

		case PDT_Left:
		playerTwoLeftPaddleMove();
		break;

		case PDT_Right:
		playerTwoRightPaddleMove();
		break;

		default:
		;
		break;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {

	//Define ports
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;

	// Define tasks
	tasks[0].state = PS_Start;
	tasks[0].period = gamePeriod;
	tasks[0].elapsedTime = tasks[0].period;
	tasks[0].TickFct = &TickFct_PlayerSelection;

	tasks[1].state = MS_Start;
	tasks[1].period = gamePeriod;
	tasks[1].elapsedTime = tasks[1].period;
	tasks[1].TickFct = &TickFct_ModeSelection;

	tasks[2].state = GS_Start;
	tasks[2].period = gamePeriod;
	tasks[2].elapsedTime = tasks[2].period;
	tasks[2].TickFct = &TickFct_GameStart;

	tasks[3].state = PDO_Start;
	tasks[3].period = gamePeriod;
	tasks[3].elapsedTime = tasks[3].period;
	tasks[3].TickFct = &TickFct_PaddleMoveOne;

	tasks[4].state = PDT_Start;
	tasks[4].period = gamePeriod;
	tasks[4].elapsedTime = tasks[4].period;
	tasks[4].TickFct = &TickFct_PaddleMoveTwo;

	// Define timer
	TimerSet(gamePeriodGCD);
	TimerOn();

	unsigned char i;

	while(1) {
		
		for(i = 0 ; i < tasksNum ; i++) {
			
			if(tasks[i].elapsedTime >= tasks[i].period) {
				tasks[i].state = tasks[i].TickFct(tasks[i].state);
				tasks[i].elapsedTime = 0;
			}

			tasks[i].elapsedTime += gamePeriodGCD;
		}

		while(!TimerFlag) {}

		TimerFlag = 0;
		
		OutB = PS_B | MS_B;
		PORTB = OutB;
	}
	
	return 0;
}