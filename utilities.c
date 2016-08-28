//----------------------------------------------------------
//
// Name: Alan Cheng
// SID: 861094564
//
// CS 120B Final Project: GlowPong
//
// Filename: utilities.c
//
// Disclaimer: Me and Natalie made this for lab, and are currently
// 			   reusing it for the final project
//
//----------------------------------------------------------


#include <avr/io.h>
#include "utilities.h"

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

unsigned char IsButtonPressed(unsigned char x, unsigned char k) {
  return GetBit(x,k) == 0;
}

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}