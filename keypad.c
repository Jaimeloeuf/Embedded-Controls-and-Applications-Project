#include <xc.h>
#include <stdint.h>
#include "keypad.h"

#define DA PORTBbits.RB0 // DA pin will be connected to INT0 interrupt pin RB0.

// Array that stores all the keypad digits based on the input truth table
unsigned char keypad_digit[] = {1, 2, 3, 0xF, 4, 5, 6, 0xE, 7, 8, 9, 0xD, 0, 0xB, 0xC};
// "Global" variable input that holds the value of the input. Optimization: Create once, used many times.
unsigned char input;

// To use this BitMask to read the Upper nibble of PORTC -> RC4-RC7
unsigned char const keypad_BitMask = 0xF0;

void Keypad_setup(void) {
	/* Setup function will set all the directional registers and set the interrupt for the DA Pin */
	
	// Keypad A-D is connected to RC 4 - 7, set as output without affecting the other bits on the PORTC register
	TRISC &= 0x0F;
	
	/* Set the interrupt to detect a rising edge on DA or RB0 or INT0 */
	// Disable all interrupt
	
	
	// Enable interrupt

	// Set to detect rising edge input.

	// Enable all interrupts
}

// Function to be called by the ISR when DA interrupts.
unsigned char keypad_ISR(void)
{
	input = keypad_digit[PORTC & keypad_BitMask];

	/* Do other things needed here */
	if (input == '')

	// return input; // Return the value keyed on the keypad
}

/*	@Doc
	This module contains the:
	- Keypad value's lookup table or map
	- The "ISR" function that will be called by the ISR to handle the interrupt
	- Pin definition of
		- DA
		- The pins connected to the Decoder output
*/