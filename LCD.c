#include <stdint.h>
#include <xc.h>
#include "LCD.h"

// Macros, confined only to this file
#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1 // RS signal for LCD
#define LCD_E PORTEbits.RE0  // E signal for LCD

unsigned char LCD_TEMP;

void LCD(uint8_t cls, uint8_t line, char *msg)
{
	if (cls)
		W_ctr_4bit(1); // Clear the display & goto home position
	switch (line)
	{
	case LINE1:
		W_ctr_4bit(0x80); // Set cursor to line 1
		break;
	case LINE2:
		W_ctr_4bit(0xc0); // Set cursor to line 2
		break;
	}
	
	for (int i = 0; msg[i]; i++) // Output message to LCD
		W_data_4bit(msg[i]);	 // Write individual character to LCD
}

void Init_LCD(void)
{ /* LCD display initialization */

	/* PORT direction registers. */
	// Use the AND bitwise operator to set bits to 0
	// Upper nibble of PORTD is for the 4 Bit data bus. All other pins are left untouched by the bitmask
	TRISD &= 0x0F;
	// RE0 and RE1 is used for the RS and E pin of the LCD. All other pins are left untouched by the bitmask
	TRISE &= 0x0C;

	// Special Sequence a) to d) required for 4-bit interface
	_delay(15);				// a) 15ms LCD power-up delay
	W_ctr_4bit(0x03);		// b) Function Set (DB4-DB7: 8-bit interface)
	_delay(5);				// c) 5ms delay
	W_ctr_4bit(0x02);		// d) Function Set (DB4-DB7: 4-bit interface)
	W_ctr_4bit(0b00101000); // Function Set - 4-bit, 2 lines, 5X7
	W_ctr_4bit(0b00001100); // Display on, cursor off
	W_ctr_4bit(0b00000110); // Entry mode - inc addr, no shift
	W_ctr_4bit(0b00000001); // Clear display & home position
}

void W_ctr_4bit(char x)
{
	/* Write control word in term of 4-bit at a time to LCD */
	LCD_RS = 0;   // Logic ?0?
	LCD_TEMP = x; // Store control word
	//LCD_TEMP >> 4 // send upper nibble of control word
	LCD_E = 1; // Logic ?1?
	LCD_DATA = LCD_TEMP;
	_delay(300);   // 0.3ms delay
	LCD_E = 0;		// Logic ?0?
	_delay(300);   // 0.3ms delay
	LCD_TEMP = x;   // Store control word
	LCD_TEMP <<= 4; // Send lower nibble of control word
	LCD_E = 1;		// Logic ?1?
	LCD_DATA = LCD_TEMP;
	_delay(300);   // 0.3ms delay
	LCD_E = 0;	// Logic 0?
	_delay(300);   // 0.3ms delay
}

void W_data_4bit(char x)
{
	/* Write text data in term of 4-bit at a time to LCD */
	LCD_RS = 1;   // Logic ?1?
	LCD_TEMP = x; // Store text data
	//LCD_TEMP >>= 4; // Send upper nibble of text data
	LCD_E = 1; // Logic ?1?
	LCD_DATA = LCD_TEMP;
	_delay(300);   // 0.3ms delay
	LCD_E = 0;		// Logic ?0?
	_delay(300);   // 0.3ms delay
	LCD_TEMP = x;   // Store text data
	LCD_TEMP <<= 4; // Send lower nibble of text data
	LCD_E = 1;		// Logic ?1?
	LCD_DATA = LCD_TEMP;
	_delay(300);   // 0.3ms delay
	LCD_E = 0;	// Logic ?0?
	_delay(300);   // 0.3ms delay
}