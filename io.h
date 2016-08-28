//----------------------------------------------------------
//
// Name: Alan Cheng
// SID: 861094564
//
// CS 120B Final Project: GlowPong
//
// Filename: io.h
//
// Disclaimer: Me and Natalie made this for lab as partners,
// 			   and are reusing it for the final project.
//
//----------------------------------------------------------

#ifndef __io_h__
#define __io_h__

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column ,const unsigned char *string);
void delay_ms(int miliSec);
#endif

