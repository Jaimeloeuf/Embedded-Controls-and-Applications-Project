#include <xc.h>
#include <stdint.h>
#include "keypad.h"

#define DA PORTAbits.RA1 // This input pin will be used as an eternal interrupt

// Array that stores all the keypad digits based on the input truth table
unsigned char keypad_digit[] = {1, 2, 3, 0xF, 4, 5, 6, 0xE, 7, 8, 9, 0xD, 0, 0xB, 0xC};
// "Global" variable input that holds the value of the input. Optimization: Create once, used many times.
unsigned char input;

void Keypad_setup(void);

// Function to be called by the ISR when DA interrupts.
unsigned char keypad_ISR(void)
{
	input = keypad_digit[PORTB & 0x0F]; // Read the lower nibble -> RB0-RB3

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