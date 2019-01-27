/*	@Doc
	This module contains the:
	- The 2D array that holds all the menu's static contents.
	- Function used to display menu items
*/

#include <stdint.h>
#include <xc.h>

// char *strs[NUMBER_OF_STRINGS] = {"foo", "bar", "bletch", ...};

// An array of pointers to constant char strings.
// char *menu[NUMBER_OF_STRINGS] = {
// 	"View current
// 	temperature",
// 	"bar",
// 	"bletch"};

char *menu1[NUMBER_OF_STRINGS] = {
	"Menu (5)",
	"s3:back s2:next"};

char *menu1[NUMBER_OF_STRINGS] = {
	"View current",
	"temperature"};

char *menu2[] = {
	"Toggle operating",
	"mode"};

char *menu3[] = {
	"View current",
	"temp. threshold"
};

char *menu3[] = {
	"Set new temp.",
	"threshold"
};

char *menu[] = {
	"Enter new temp.",
	""
};

char *menu[] = {
	"Set sprinkler strength"
};


/*
As the user types in their input, the items on the menu will disappear
LCD will then start displaying the input on the screen

How should the user exit that particular menu?
2 buttons to switch between menu items
Press a button to enter
Press E to exit
Press D to show a decimal point if allowed (Flash invalid for a second.)
*/
char *menu[] = {
	"Enter strength",
	"as a percentage"
};

char **menu[Number of lines to be stored] = {
	menu1,
	menu2,
	menu3,
	menu4};

// Use the below function to choose what to display on the LCD.
unsigned char menu_disp(uint8_t menu_item, uint8_t sub_menu_item)
{
	// Get the static part of the message to display from the 2D array
	// message = menu[menu_item][sub_menu_item];

	// Get the pointer to the current menu content
	current_menu = menu[menu_item];
	// Get the pointer to the current sub menu content.
	current_menu = current_menu[sub_menu_item];

	int *arrop[3];
	int a = 10, b = 20, c = 50, i;

	arrop[0] = &a;
	arrop[1] = &b;
	arrop[2] = &c;

	for (i = 0; i < 3; i++)
	{
		printf("Address = %d\t Value = %d\n", arrop[i], *arrop[i]);
	}
}
