#ifndef timer_H
#define timer_H

// Timer interrupt flag definition. Will be used by the ISR to check for Interrupt source.
#define timeFlag INT0IF
// Function to setup all the registers, ports and everything before using the Timer.
void Timer_setup(void);
// Call this function to start the timer, when timer overflows, CPU will be interrupted with the IF, timeFlag
void timer_start(void);
// The function or routine that will be called when the source of the interrupt is from the timer
int timer_ISR(void);

#endif