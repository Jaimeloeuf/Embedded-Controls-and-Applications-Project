#include <xc.h>
#include <stdint.h>

#define DA PORTAbits.RA1 // This input pin will be used as an eternal interrupt

// Array that stores all the keypad digits based on the input truth table
unsigned char keypad_digit[] = {1, 2, 3, 0xF, 4, 5, 6, 0xE, 7, 8, 9, 0xD, 0, 0xB, 0xC};

void interrupt ISR(void)
{
	// Check the interrupt flag instead of DA. // Make DA into an EXTINT, and keypad value will be read in ISR
	if (DA == HIGH)
	{
		while (!PORTAbits.RA0)
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