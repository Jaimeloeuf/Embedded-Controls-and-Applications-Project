#include "config.h" // Header file contains any configuration bits needed to be set by the debugger
#include <xc.h>
#include <stdlib.h> // Where is this used??
#include <stdint.h> // Used to get definition for uint8_t and other standard types. To convert to use primitives ltr.

/* The target board uses 4 MHz oscillator module */
// PIC18F4520 Configuration Bit Settings
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
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

*/

void interrupt ISR(void)
{
	if (DA == HIGH)
	{
		// call the Keypad interrupt function here
	}
	else if (/* Other interrupt flags... */)
	{
	}
	else
	{
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



	/* Put MCU to sleep instead of a infinite while loop */
	sleep(); // xc8 compiler library function
	/* Idle mode means, CPU clock sleeps and peripheral continue to work.
		Sleep mode means, all selected oscillators stop. */
}