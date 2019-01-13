#include <xc.h>

// Regarding Timer
/*
A timer is a clock oscillator feeding a counter - a pre-scaler goes between the clock and counter, a post-scaler goes after the counter. There are specific advantages for either.
Prescaler: Generation of the desired frequency.
Postscaler: Management of the occurrence of the interrupt
*/

// @Todo implement 2 functions that allow timers to be called and used
void start_timer();
void stop_timer();