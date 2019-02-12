#ifndef timer_H
#define timer_H

// Timer interrupt flag definition. Will be used by the ISR to check for Interrupt source.
#define timeFlag TMR0IF
// Function to setup all the registers, ports and everything before using the Timer.
void timer_setup(void);
// The function or routine that will be called when the source of the interrupt is from the timer
void timer_ISR(void);
// Functions to start and stop the timer
void timer_start(void);
void timer_stop(void);

#endif