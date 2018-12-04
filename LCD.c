#include <stdint.h>
#include <xc.h>
#include "LCD.h"

// Macros, confined only to this file
#define LINE1 1
#define LINE2 2
#define CLS 1
#define NO_CLS 0
#define LCD_DATA PORTD		 // Data line for LCD D0-D7
#define LCD_RS PORTBbits.RB5 // RS signal for LCD
#define LCD_E PORTBbits.RB4  // E signal for LCD

void LCD(uint8_t cls, uint8_t line, char *msg)
{
	Init_LCD(); // Initialize LCD to 8-bit interface with multiple line
	if (cls)
		LCD_sendCW(0b00000001); // Clear the display
	switch (line)
	{
	case LINE1:
		LCD_sendCW(0b00000010);
		break; // Return cursor to LINE1 Home position
	case LINE2:
		LCD_sendCW(0b11000000);
		break; // Return cursor to LINE2 Home position
	}
	for (uint8_t i = 0; *(msg + i) != 0; i++)
		LCD_sendData(*(msg + i));
}
void Init_LCD()
{							// Initializes the LCD
	LCD_sendCW(0b00111000); // Function Set - 8-bit, 2 lines, 5X7
	LCD_sendCW(0b00001100); // Display on, cursor on
	LCD_sendCW(0b00000110); // Entry mode - inc addr, no shift
}
void LCD_sendCW(char x)
{				  // Write a 8-bit Control word to LCD
	LCD_RS = 0;   // To send a control word
	LCD_E = 1;	// Set Enable to "High" while setting everything up.
	LCD_DATA = x; // Put data onto the data line
	LCD_E = 0;	// The 1-0 transition will latch data on data line into LCD
	_delay(1000); // 2ms delay
}
void LCD_sendData(char x)
{				// Write 8-bit Text Data for LCD
	LCD_RS = 1; // To send data in. Non control word
	LCD_E = 1;  // Set Enable to "High" while setting everything up.
	LCD_DATA = x;
	LCD_E = 0;   // The 1-0 transition will latch data on data line into LCD
	_delay(500); // 1ms delay
}