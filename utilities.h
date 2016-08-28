//----------------------------------------------------------
//
// Name: Alan Cheng
// SID: 861094564
//
// CS 120B Final Project: GlowPong
//
// Filename: utilities.h
//
// Disclaimer: Me and Natalie made this for lab, and are currently
// 			   reusing it for the final project
//
//----------------------------------------------------------

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b);
unsigned char GetBit(unsigned char x, unsigned char k);
unsigned char IsButtonPressed(unsigned char x, unsigned char k);
void ADC_init();

#endif