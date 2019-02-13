#ifndef GLOBAL_STATE_H
#define	GLOBAL_STATE_H

#define uint8_t unsigned char

// Man Mode = 0; Auto Mode = 1;
uint8_t mode = 0;

// LED definitions
#define auto_LED PORTDbits.RD0
#define man_LED PORTDbits.RD1

// Threshold value for use in auto mode
uint8_t threshold = 100;

// Function to toggle and get the new mode
uint8_t toggle_mode(void);

// Flag to check if user is entering a numerical input
uint8_t input_flag = 0;

// LCD character's display buffer
char display[17];

#endif
