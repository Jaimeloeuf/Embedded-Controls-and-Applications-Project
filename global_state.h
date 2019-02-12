#ifndef GLOBAL_STATE_H
#define	GLOBAL_STATE_H

// Man Mode = 0; Auto Mode = 1;
uint8_t mode = 0;

// Threshold value for use in auto mode
uint8_t threshold = 100;

// Function to toggle and get the new mode
uint8_t toggle_mode(void);

// LCD character's display buffer
char display[17];

#endif
