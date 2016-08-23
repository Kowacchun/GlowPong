#ifndef __UTILITIES_H__
#define __UTILITIES_H__

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b);
unsigned char GetBit(unsigned char x, unsigned char k);
unsigned char IsButtonPressed(unsigned char x, unsigned char k);
void ADC_init();

#endif