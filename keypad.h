#ifndef keypad_H
#define keypad_H

// Keypad interrupt flag, or DA's definition. Will be used by the ISR to check for Interrupt source.
#define keyFlag INTCONbits.INT0IF
// Function to setup all the registers, ports and everything for Keypad to be ready for use.
void Keypad_setup(void);
// The function or routine that will be called when the source of the interrupt is from the Keypad's DA pin.
unsigned char keypad_ISR(void);

#endif