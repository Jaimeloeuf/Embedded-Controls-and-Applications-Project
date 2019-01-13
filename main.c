#include "config.h"
#include <xc.h>
#include <stdlib.h>
#include <stdint.h>

/* The target board uses 4 MHz oscillator module */
// PIC18F4520 Configuration Bit Settings
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#define _XTAL_FREQ 4000000 // Fosc  frequency for _delay()  library 4MHz

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

// 'Buzzer' Macros
#define SPEAKER PORTEbits.RE0
void speaker(count)
{
	// Sound a specific number of times per call. Should this be done in software delats or should this be done with hardware interrupts
	for()
	for (int n = 0; n < 500; n++)
	{
		SPEAKER = 1;
		_delay(10);
		SPEAKER = 0;
		_delay(500);
	}
}

#define DA PORTAbits.RA1 // Make this into a Interrupt flag
void interrupt ISR(void)
{
	if (DA == HIGH)
	{
		// Check the interrupt flag instead of DA. Perhaps in this case, DA is the interrupt flag?

		while (!PORTAbits.RA0) // Make DA into an EXTINT, and keypad value will be read in ISR
			_7Seg(num1, num2);

		value[count] = keypad_digit[PORTB & 0x0F]; // Read the lower nibble. RB0-RB3

		if (value[count] == keypad_digit['F'])
		{
			// Reset the count shit when F is encountered
		}

		// Clear the interrupt flag
		DA = 0;
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

/*
OSSCON register is used to select the current run mode
*/

void ADC_setup()
{
	// Set ADC input pin/channel
	// Modify the TRIS registers to match above ADC input selection
}

void start_timer();
void stop_timer()

void main(void)
{
	// Set the I/O tri-state buffers
	// @TODO Need to change the ADCON1 for the ADC usage
	ADCON1 = 0x0F;		// Set ports A,B & E as digital I/O
	TRISA = 0b11001111; // RA0(Keypad DA)  RA1(Touch Sensor Output)
	TRISB = 0b11001111; // RB0-RB3 INPUT for Keypad A-D // RB4 & 5 OUTPUT for LCD interface RS & E
	TRISC = 0;			// PORTC 0-6 used for Output to 7Seg // RC7 used for LIGHTBULB
	TRISD = 0;			// Entire PORTD used for LCD output
	TRISE = 0;			// RE0 is used for speaker // RE1 and RE2 used as output for SL1 and SL2 // Must be output to use PORTD as GPIO

	// Read config and password from EEPROM

	// Set any initial values
	PORTA =



	/* Put MCU to sleep instead of a infinite while loop */
	sleep(); // xc8 compiler library function
	/* Idle mode means, CPU clock sleeps and peripheral continue to work.
		Sleep mode means, all selected oscillators stop. */
}



/*

Tech needed to be included:
- ADC to read a analog input
- Hardware PWM to simulate analog output
- Harware timer to create delays or smth
- Sleep and other power management shit

*/



// Regarding Timer
/*
A timer is a clock oscillator feeding a counter - a pre-scaler goes between the clock and counter, a post-scaler goes after the counter. There are specific advantages for either.
Prescaler: Generation of the desired frequency.
Postscaler: Management of the occurrence of the interrupt
*/