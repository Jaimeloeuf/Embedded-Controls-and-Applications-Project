#ifndef menu_H
#define menu_H

// Global variable to keep track of the current menu to maintain state between interrupts.
int8_t c_menu = 0;

// Functions to navigate the menu
void next(void);
void previous(void);

//unsigned char menu_disp(unsigned char menu_item, unsigned char sub_menu_item);
uint8_t menu_disp(uint8_t menu_item);

#endif