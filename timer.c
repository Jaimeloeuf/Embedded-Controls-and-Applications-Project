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

	TMR0H = 0x3C;
	TMR0L = 0xB0; // TRM0H:L = 0x3CB0
	T0CON = 0b10000010;
	INTCON = 0b11100000; //GIEH=1, GIEL=1, TMR0IE = 1, TMR0IF=0
}

// Function to actually
void timer_init(int f(int a, int b), uint16_t time, ...)
{
	// Step one is to make the 'time' input usable
	
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

void interrupt ISR(void)
{
	if (INTCONbits.TMR0IF)
	{
		TMR0H = 0x3C;
		TMR0L = 0xB0; // TMR0H:L=0x3CB0 = 15536
		INTCONbits.TMR0IF = 0;
	}
}
