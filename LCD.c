#include <stdint.h>
#include <xc.h>
#include "LCD.h"

#define _XTAL_FREQ 4000000

// Macros, confined only to this file
#define LCD_DATA PORTD		 // Data line for LCD D0-D7
#define LCD_RS PORTEbits.RE1 // RS signal for LCD
#define LCD_E PORTEbits.RE0  // E signal for LCD

// Global variable to maintain state off the databus connection type. 1 for 8 Bit connection, 0 for 4 Bit connection.
uint8_t CONN_TYPE;

const char MESS[] = "ECAPP LAB 3";
void example_code(void)
{
	// Initialise LCD to use 4-bit databus interface, with multi-line display
	Init_LCD(4);

	for (i = 0; MESS[i]; i++) // Output message to LCD
		W_data_4bit(MESS[i]); // Write individual character to LCD

	// Below is example code on using the LCD
	W_ctr_4bit(0xc0);		  // Set cursor to line 2
	itoa(buff, 12, 10);		  // function itoa is used to convert integer stored at result to ASCII and keep to MESS
	for (i = 0; buff[i]; i++) // Write data to LCD up to null
		W_data_4bit(buff[i]); // Write character to LCD
}

void LCD(uint8_t cls, uint8_t line, char *msg)
{
	// Have a check for the CONNECTION TYPE to determine which functions to use.
	switch (CONN_TYPE)
	{
	case 0:
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
		for (uint8_t i = 0; *(msg + i) != 0; i++)
			LCD_sendData(*(msg + i));

		break;
	case 1:
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
		break;

	default:
		return 0; // Return 0 to indicate failure
	}
	return 1; // Return 1 to indicate success.
}

uint8_t Init_LCD(uint8_t data_bus_width)
{
	// User can choose to either use the 8Bit or the 4Bit databus version to connect to the LCD
	switch (data_bus_width)
	{
	case 4:
		// Set the variable that keeps track of the connection type
		CONN_TYPE = 0;
		// Initialise the LCD
		Init4bit();
		break;
	case 8:
		// Set the variable that keeps track of the connection type
		CONN_TYPE = 1;
		// Initialise the LCD
		Init8bit();
		break;
	// Onlt 4 or 8 are valid inputs. If anything else, will return a 0 for false/failed.
	default:
		return 0;
	}
	// Return 1 for true/operation-success
	return 1;
}

// Function to Initialize LCD to 8-bit interface with multiple line
void Init8bit()
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

// Function to Initialize LCD to 4-bit data interface with multiple line
void Init4bit()
{
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
	_delay(1000);   // 1ms delay
	LCD_E = 0;		// Logic ?0?
	_delay(1000);   // 1ms delay
	LCD_TEMP = x;   // Store control word
	LCD_TEMP <<= 4; // Send lower nibble of control word
	LCD_E = 1;		// Logic ?1?
	LCD_DATA = LCD_TEMP;
	_delay(1000); // 1ms delay
	LCD_E = 0;	// Logic 0?
	_delay(1000); // 1ms delay
}
void W_data_4bit(char x)
{
	/* Write text data in term of 4-bit at a time to LCD */
	LCD_RS = 1;   // Logic ?1?
	LCD_TEMP = x; // Store text data
	//LCD_TEMP >>= 4; // Send upper nibble of text data
	LCD_E = 1; // Logic ?1?
	LCD_DATA = LCD_TEMP;
	_delay(1000);   // 1ms delay
	LCD_E = 0;		// Logic ?0?
	_delay(1000);   // 1ms delay
	LCD_TEMP = x;   // Store text data
	LCD_TEMP <<= 4; // Send lower nibble of text data
	LCD_E = 1;		// Logic ?1?
	LCD_DATA = LCD_TEMP;
	_delay(1000); // 1ms delay
	LCD_E = 0;	// Logic ?0?
	_delay(1000); // 1ms delay
}