#include "config.h"
#include <xc.h>
#include <stdint.h>

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

// To move function into external utils lib
char numberToWord(int num)
{
	switch (num)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	}
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

#define LIGHT_WRONG 0
#define LIGHT_CORRECT 1
#define LIGHT_ON PORTCbits.RC7 = 1
#define LIGHT_OFF PORTCbits.RC7 = 0
void lightbulb(uint8_t pattern) // TO CHANGE THE PORTS USED FOR THE LIGHT BULB
{
	switch (pattern)
	{
	case LIGHT_CORRECT: // Bight intensity. Holds for about 1 second
		for (int n = 0; n < 10; n++)
		{
			LIGHT_ON;
			_delay(900); // Pulse HIGH
			LIGHT_OFF;
			_delay(100); // Pull LOW
		}
		break;
	case LIGHT_WRONG: // Quick Flashing for about 0.2 second
		for (int n = 0; n < 10; n++)
		{
			LIGHT_ON;
			_delay(100);
			LIGHT_OFF;
			_delay(900);
		}
		break;
	}
	LIGHT_OFF; // Off the bulb at the end
}

unsigned char keypad_digit[] = {1, 2, 3, 0xF, 4, 5, 6, 0xE, 7, 8, 9, 0xD, 0, 0xB, 0xC};
uint8_t game(uint8_t num1, uint8_t num2) // Main function to execute when a button is pressed. It will send signal for others to do stuff
{
	// Listen to keypad until user press F for finnish input.

	for (unsigned char count = 0; count < 2; count++)
	{
		while (!PORTAbits.RA0) // Make DA into an EXTINT, and keypad value will be read in ISR
			_7Seg(num1, num2);
		value[count] = keypad_digit[PORTB & 0x0F]; // Read the lower nibble. RB0-RB3
		if (value[0] == ans)					   // If ans is only 1 digit
			return 1;
		while (PORTAbits.RA0 == 1)
		{
			_7Seg(num1, num2);
		}
	}

	// Return the full value? Or should I call functions from here
	return ((value[0] * 10) + value[1] == num1 + num2) ? 1 : 0;
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
	// Interrupts
	GIE = 0;

	INTCON2
	INTCON3

	GIE = 1;
}

void ADC_setup()
{
}

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

		return;
}

// Old deprecated example code

// _7Seg(0, 0); // Reset the 7 seg displays to nothing
// LIGHT_OFF;   // Off the bulb first
// LCD(CLS, LINE1, "Press touch");
// LCD(NO_CLS, LINE2, "sensor to play!");

// if (game(num1, num2))
// {
// 	_7Seg(0, 0); // Reset the 7 seg displays to nothing
// 	LCD(CLS, LINE1, "You are correct!");
// 	LCD(NO_CLS, LINE2, "Congratulations!");
// 	PORTAbits.RA4 = 1; // LED
// 	speaker(SOUND_CORRECT);
// 	lightbulb(LIGHT_CORRECT);
// }
// else
// {
// 	_7Seg(0, 0); // Reset the 7 seg displays to nothing
// 	LCD(CLS, LINE1, "Incorrect!");
// 	LCD(NO_CLS, LINE2, "Try again!");
// 	PORTAbits.RA5 = 1; // LED
// 	speaker(SOUND_WRONG);
// 	lightbulb(LIGHT_WRONG);
// }


// Regarding Timer
/*
A timer is a clock oscillator feeding a counter - a pre-scaler goes between the clock and counter, a post-scaler goes after the counter. There are specific advantages for either.
Prescaler: Generation of the desired frequency.
Postscaler: Management of the occurrence of the interrupt
*/