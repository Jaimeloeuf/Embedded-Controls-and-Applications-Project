/*	@Doc
    This module contains the:
    - The 2D array that holds all the menu's static contents.
    - Function used to display menu items
 */

#include <stdint.h>
#include <xc.h>
#include "global_state.h"
#include "LCD.h"
#include "menu.h"
#include "pwm.h"

// An array of pointers to constant char strings.
char *menu0[] = {
    "Menu (5)",
    "s7:back s8:next"
};
char *menu1[] = {
    "View current",
    "temperature"
};
char *menu2[] = {
    "Toggle mode",
    ""
};
char *menu3[] = {
    "View current",
    "temp. threshold"
};
char *menu4[] = {
    "Set new temp.",
    "threshold"
};
char *menu5[] = {
    "Toggle speed",
    ""
};
char *error[] = {
    "ERROR!",
    "" // Empty second line.
};

// Function to display out the menus
void disp(char **menu) {
    LCD(CLS, LINE1, menu[0]);
    LCD(NO_CLS, LINE2, menu[1]);
}

// Use the below function to choose what the menu to display on the LCD.
uint8_t menu_disp(uint8_t menu_item) {
    // Switch to display the menu based on the input value, where some are dynamically generated
    switch (menu_item) {
        case 0:
            disp(menu0);
            break;
        case 1:
            disp(menu1);
            break;
        case 2:
            disp(menu2);
            // Dynamically generate Menu based on the current operating mode
            if (mode) {
                char current_mode[] = "current: Auto";
                LCD(NO_CLS, LINE2, current_mode);
            } else {
                char current_mode[] = "current: Man";
                LCD(NO_CLS, LINE2, current_mode);
            }
            break;
        case 3:
            disp(menu3);
            break;
        case 4:
            disp(menu4);
            break;
        case 5:
            disp(menu5);
            // Dynamically generate Menu based on the speed of the motor
            if (speed) {
                char current_speed[] = "current: Full";
                LCD(NO_CLS, LINE2, current_speed);
            } else {
                char current_speed[] = "current: Half";
                LCD(NO_CLS, LINE2, current_speed);
            }
            break;
        case 10:
            disp(error);
            break;
        default:
            // Return 0 to indicate menu item does not exist
            return 0;
    }
    // Store the selected menu item after displaying, to maintain state across interrupts
    c_menu = menu_item;
    // All cases will return 1 to indicate menu exists and successfully switched by menu ID increment
    return 1;
}

void previous(void) {
    // Decrement the menu page
    --c_menu;
    if (c_menu < 0) {
        c_menu = 5;
    }
    menu_disp(c_menu);
}

void next(void) {
    // Increment the menu page
    ++c_menu;
    if (c_menu > 5) {
        c_menu = 0;
    }
    menu_disp(c_menu);
}