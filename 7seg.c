#include <xc.h>
#include <stdint.h>

// Lookup table for the 7Seg displays.
uint8_t SevenSeg[7] = {0xFF, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010};
void _7Seg(uint8_t seg1, uint8_t seg2)
{
	// Perhaps add a method to off one of the 7seg? E.g. when val read is -1, off the SL
	PORTC = SevenSeg[seg1];
	PORTEbits.RE1 = 0; // On SL1
	PORTEbits.RE2 = 1; // Off SL2
	_delay(200);
	PORTC = SevenSeg[seg2];
	PORTEbits.RE1 = 1; // Off SL1
	PORTEbits.RE2 = 0; // On SL2
	_delay(200);
}
