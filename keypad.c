/*	@Doc
    This module contains the:
    - Keypad value's lookup table or map
    - The "ISR" function that will be called by the ISR to handle the interrupt
    - Pin definition of
        - DA
        - The pins connected to the Decoder output
 */

// Set 'Fosc' frequency, needed by the delay function call
#define _XTAL_FREQ 4000000
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <string.h>
#include "global_state.h"
#include "keypad.h"
#include "LCD.h"
#include "menu.h"
#include "adc.h"
#include "pwm.h"


// Setup function will set all directional registers and the interrupt for the DA Pin
void Keypad_setup(void) {
    // Keypad A-D is connected to RC 4 - 7, set as input without affecting the other bits on the PORTC register
    TRISC |= 0xF0;

    /* Set the interrupt to detect a rising edge on DA or RB0 or INT0 */
    // Disable all interrupt
    GIE = 0;
    // Clear the INT0 external interrupt
    INTCONbits.INT0IF = 0;
    // Enable the INT0 external interrupt
    INTCONbits.INT0IE = 1;
    // Set INT0 to interrupt on rising edge
    INTCON2bits.INTEDG0 = 1;
    // Enable all interrupts
    GIE = 1;
}

// Array that stores all the keypad digits based on the input truth table
unsigned char keypad_digit[] = {1, 2, 3, 0xF, 4, 5, 6, 0xE, 7, 8, 9, 0xD, 0, 0xB, 0xC};
// "Global" variable input that holds the value of the input. Optimization: Create once, used many times.
unsigned char input;

// Store the input numbers read into input_num, for when E is pressed again
// Every time menu item is changed, the inputs should be cleared
uint16_t input_num = 0;

// To use this BitMask to read the Upper nibble of PORTC -> RC4-RC7
unsigned char const keypad_BitMask = 0xF0;

// const char array to print out.
char press_F[] = "Press F to exit";

// Function to display the current temperature threshold value
void display_threshold(void) {
    LCD(CLS, LINE1, itoa(display, threshold, 10));
    LCD(NO_CLS, LINE2, press_F);
}

// Flag to indicate if menu is currently on a "sub menu" stage in the middle of input
uint8_t sub_menu_flag = 0;

unsigned char keypad_ISR(void) {
    // Read the encoder output from PORTC with bit mask and lookup the value
    input = keypad_digit[(PORTC & keypad_BitMask) >> 4];

    /* Do other things needed here */
    switch (input) {
        case 10: case 11: case 13:
            break; // If the user pressed A-D, ignore the input by just breaking out of switch()
        case 12:
            // If user pressed the C, clear input key
            // Check if user was entering a numerical digit before pressing clear
            if (input_flag) {
                // Reset the input value
                input_num = 0;
                // Display the new value on the screen
                LCD(NO_CLS, LINE2, itoa(display, input_num, 10));
            }
            break;
        case 14:
            // E: Enter key
            if (c_menu == 1) {
                // Display the current temperature
                LCD(CLS, LINE1, itoa(display, adc_read(), 10));
                LCD(NO_CLS, LINE2, press_F);
            } else if (c_menu == 2) {
                toggle_mode();
                // Call the init functions of the different modes
                // Make sure motor is off when transitioning into man mode
                motor_stop();
                // Display the menu again after updating the current mode
                menu_disp(2);
            } else if (c_menu == 3) {
                display_threshold();
            } else if (c_menu == 4) {
                if (input_flag) {
                    // If user is entered a number and pressed E again.
                    char thres_msg[] = "Threshold set:";
                    LCD(CLS, LINE1, thres_msg);
                    // Set the threshold value with the input number
                    threshold = input_num;
                    // Display the new threshold value
                    display_threshold();
                    // Clear the input flag
                    input_flag = 0;
                    // Clear sub_menu_flag as the numbers should not be displayed when keyed anymore
                    sub_menu_flag = 0;
                } else {
                    // Allow user to type in a new temp threshold
                    char press_E[] = "Press E to set";
                    LCD(CLS, LINE1, press_E);
                    // Set flag to indicate that PC inside the sub-menu now
                    sub_menu_flag = 1;
                }
            } else if (c_menu == 5) {
                // Toggle the speed of the sprinkler
                toggle_speed();
                // If the motor is currently on, restart the motor to run with the new speed
                if (motor_state)
                    motor_restart();
                // Display the menu again after updating the current mode
                menu_disp(5);
            }
            break;
        case 15:
            // F: Finished key to go back to home/main menu
            menu_disp(0);
            break;
        default:
            // Default is where the input is from 0 - 9
            
            // Only menu 4 accepts numerical input from keypad
            if (c_menu == 4 && sub_menu_flag) {
                // Set a number input in progress flag for the case E of menu 4 to read
                input_flag = 1;
                // Calculate the number entered
                input_num = (input_num * 10) + input;

                if (input_num > 255) {
                    // Display the error on the screen
                    menu_disp(10);
                    // Create a error description message
                    char err[] = "Number too big";
                    // Display error description message
                    LCD(NO_CLS, LINE2, err);
                    // Clear the input number
                    input_num = 0;
                    // Clear the input flag
                    input_flag = 0;
                }
                LCD(NO_CLS, LINE2, itoa(display, input_num, 10));
            }
    }
}