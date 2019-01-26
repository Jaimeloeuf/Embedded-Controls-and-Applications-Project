#include <stdarg.h>
#include <xc.h>

// Regarding Timer
/*
A timer is a clock oscillator feeding a counter - a pre-scaler goes between the clock and counter, a post-scaler goes after the counter. There are specific advantages for either.
Prescaler: Generation of the desired frequency.
Postscaler: Management of the occurrence of the interrupt
*/

/* Setup the timer registers in this function */
void timer_setup(void)
{
	// Add in all the values and stuff.
}

// Function to actually 
void timer_init(int f(int a, int b), uint16_t time, ...)
{
	
}

void timer_action()
{
	// This function takes in a function pointer.
	// This function will run when the time is out, by calling the function passed in using the function pointer.
}

/*	@Flow used
	1. The user will set a time to time out in, can indicate if you want the time to be seconds or milliseconds
	2. Pass in the function to be executed when time is up

	// Basically fucking set timeout all over again.
*/