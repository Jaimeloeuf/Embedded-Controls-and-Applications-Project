#include "config.h" // Header file contains any configuration bits needed to be set by the debugger
#include <xc.h>
#include <stdlib.h> // Where is this used??
#include <stdint.h> // Used to get definition for uint8_t and other standard types. To convert to use primitives ltr.

// My own header files for the libs/modules
#include "keypad.h" // Keypad reader interface
#include "adc.h"	// ADC control and reader functions
#include "timer.h"  // Peripheral timer controller
#include "7seg.h"   // Dual Seven Segment interface lib
#include "LCD.h"	// LCD interface lib
#include "utils.h"  // Utilities functions

/* The target board uses 4 MHz oscillator module */
// PIC18F4520 Configuration Bit Settings
#pragma config OSC = XT // Oscillator Selection bits (XT oscillator)
// Set 'Fosc' frequency, needed by the delay function call
#define _XTAL_FREQ 4000000

/*	@Doc
	This is the main file, and it should only contain the:
	- main function
	- The interrupt service routines
	- Interrupt setup code
	- Power management code
	All other functionalities should be imported in from other libs.

	@Todo
	Split the ISR up to deal with High and Low priority interrupts seperately

	Tech needed to be included:
	- ADC to read a analog input
	- Hardware PWM to simulate analog output
	- Harware timer to create delays or smth
	- Sleep and other power management shit

	The ISR in this file will handle the interrupt source checking and clearing of the interrupt flag when done.
*/

// The ISR is just a 'Switch' in charge of calling the "ISR" of the different libs/modules
void interrupt ISR(void)
{
	/*	@Steps
		1. Check for interrupt source by checking all the interrupt flags.
		2. Call the "ISR" functions
			Clear the interrupt flag.
	*/

	if (keyFlag) // Check if DA went high
	{
		// call the Keypad interrupt function
		keypad_ISR();
		// Clear the interrupt flag
		keyFlag = 0;
	}
	else if (adcFlag)
	{
		// Call the ADC interrupt function and get the adc value back
		adc_ISR();
		// Clear the interrupt flag
		adcFlag = 0;
	}
	else if (timeFlag)
	{
		// Timer overflow interrupt set.
		// The functions and everything else is dealt with in the Timer function.
		timer_ISR();

		// Clear the interrupt flag
		timeFlag = 0;
	}
	else if (/* Other interrupt flags... */)
	{
	}
	else
	{
		// If the source cannot be determined, set error flag>
	}
}

void interrupt_setup()
{
	// Disable all Interrupts
	GIE = 0;
	INTCONbits.GIEH = 0;

	INTCON2
	INTCON3

	// Enable all interrupts
	GIE = 1;
}

void main(void)
{
	// To use OSSCON register to select the current run mode at startup

	// Set the I/O tri-state buffers
	// @TODO Need to change the ADCON1 for the ADC usage
	ADCON1 = 0x0F;		// Set ports A,B & E as digital I/O
	TRISA = 0b11001111; // RA0(Keypad DA)  RA1(Touch Sensor Output)
	TRISB = 0b11001111; // RB0-RB3 INPUT for Keypad A-D // RB4 & 5 OUTPUT for LCD interface RS & E
	TRISC = 0;			// PORTC 0-6 used for Output to 7Seg // RC7 used for LIGHTBULB
	TRISD = 0;			// Entire PORTD used for LCD output
	TRISE = 0;			// RE0 is used for speaker // RE1 and RE2 used as output for SL1 and SL2 // Must be output to use PORTD as GPIO

	// Read config and password from EEPROM --> needed?

	// Set any initial values
	PORTA =


	/*	Infinite loop so when it wakes and finishes the ISR and continue on the sleep line, it will loop back
		to go sleep again. This is done to prevent the program from ending after waking from sleep, similiar
		to the concept of a never ending event-loop in JavaScript */
	while (1)
	{
		int x; // Stuff that I want to do before going back to sleep... can be anything. The int x is just a placeholder.
		SLEEP(); // xc8 compiler library sleep function
	}
	// Idle mode means, CPU clock sleeps and peripheral continue to work. Sleep mode means, all selected oscillators stop.
}