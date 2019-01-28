/*	@Doc
	This module contains the:
	- The 2D array that holds all the menu's static contents.
	- Function used to display menu items
*/

#include <stdint.h>
#include <xc.h>
#include "LCD.h"

// An array of pointers to constant char strings.
char *menu0[NUMBER_OF_STRINGS] = {
	"Menu (5)",
	"s3:back s2:next"};

char *menu10[NUMBER_OF_STRINGS] = {
	"View current",
	"temperature"};

char *menu20[] = {
	"Toggle operating",
	"mode"};

char *menu21[] = {
	"Current Mode:",
	""}; // Second line to display the current mode as either man or auto, after the mode toggle

char *menu30[] = {
	"View current",
	"temp. threshold"
};

char *menu31[] = {
	"Current temp.",
	""}; // Second line to display the reading that was taken immediately after calling menu30

char *menu40[] = {
	"Set new temp.",
	"threshold"
};

char *menu41[] = {
	"Enter new temp.",
	"" // Second line is to display the user input.
};

char *menu50[] = {
	"Set sprinkler",
	"strength"
};

char *menu51[] = {
	"Percent of Max:",
	"" // Second line is to display the user input.
};

// Every single menu should have a corresponding function to deal with it.


/*
As the user types in their input, the items on the menu will disappear
LCD will then start displaying the input on the screen

How should the user exit that particular menu?
2 buttons to switch between menu items
Press a button to enter
Press E to exit
Press D to show a decimal point if allowed (Flash invalid for a second.)
*/


/* To make the input use variable arguements and default to 0 */

// Use the below function to choose what to display on the LCD.
unsigned char menu_disp(uint8_t menu_item, uint8_t sub_menu_item)
{
	// Get the static part of the message to display from the 2D array
	// message = menu[menu_item][sub_menu_item];
	// get the menu ID
	menuID = (menu_item * 10) + sub_menu_item;

	switch (menuID)
	{
		case 0:
			menu0[0];
			menu0[1];
			break;
	
		default:
			break;
	}
}
