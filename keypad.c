/*	@Doc
	This module contains the:
	- Keypad value's lookup table or map
	- The "ISR" function that will be called by the ISR to handle the interrupt
	- Pin definition of
		- DA
		- The pins connected to the Decoder output
*/

#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "keypad.h"

#define DA PORTBbits.RB0 // DA pin will be connected to INT0 interrupt pin RB0.

// Array that stores all the keypad digits based on the input truth table
unsigned char keypad_digit[] = {1, 2, 3, 0xF, 4, 5, 6, 0xE, 7, 8, 9, 0xD, 0, 0xB, 0xC};
// See if the below array is valid.
//unsigned char keypad_digit[] = {1, 2, 3, 'F', 4, 5, 6, 'E', 7, 8, 9, 'D', 0, 'B', 'C'};
// "Global" variable input that holds the value of the input. Optimization: Create once, used many times.
unsigned char input;

// To use this BitMask to read the Upper nibble of PORTC -> RC4-RC7
unsigned char const keypad_BitMask = 0xF0;

/* Setup function will set all the directional registers and set the interrupt for the DA Pin */
void Keypad_setup(void)
{
	// Keypad A-D is connected to RC 4 - 7, set as output without affecting the other bits on the PORTC register
	TRISC &= 0x0F;

	/* Set the interrupt to detect a rising edge on DA or RB0 or INT0 */
	// Disable all interrupt
	INTCONbits.GIE = 0;
	// Enable the INT0 external interrupt
	INTCONbits.INT0IE = 1;
	// Set INT0 to interrupt on rising edge
	INTCON2bits.INTEDG0 = 1;
	// Enable all interrupts
	INTCONbits.GIE = 1;
}

// Function to be called by the ISR when DA interrupts.
// Something like a menu function that deals with the users selection in the menu.
unsigned char keypad_ISR(void)
{
	input = keypad_digit[PORTC & keypad_BitMask];

	/* Do other things needed here */
	switch (input)
	{
	case 'A':

		break;
	case 'B':

		break;
	case 'C':

		break;
	case 'D':

		break;
	case 'E':

		break;
	case 'F':

		break;

	default:
		break;
	}

	// return input; // Return the value keyed on the keypad
}
