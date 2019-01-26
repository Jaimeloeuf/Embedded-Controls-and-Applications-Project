#include <xc.h>
#include "keypad.h"

/*	@Doc
	This module contains the PWM control
	The operation of CCP1 module is controlled by register CCP1CON.
	For PWM mode, Timer2 is used for generating the switching frequency.

*/

#define DA PORTAbits.RA1 // This input pin will be used as an eternal interrupt

int power_output;

// Use this function to set output power.
void set_output_power(int output_percentage)
{
	/* Input parameter:
		output_percentage: A decimal up to 100 that
	*/
	if (output_percentage > 100)
		output_percentage = 100;
	else if (output_percentage < 0)
		output_percentage = 0;

	// Calculate the duty cycle then store in the variable.
	power_output = output_percentage;
}

void motor_setup(int output_percentage)
{
	// Call function to set the percentage of power to be output
	set_output_power(output_percentage);


	// RC2 will be used as output, so set the pin usage type here. All other pins are left untouched by the bitmask
	TRISC &= 0xFB;

	T2CON = 0b00000101;   // On Timer 2, postscale = 1:1, prescale = 1:4
	PR2 = 64;			  // Set PR2 = 64 for 52 µs
	CCPR1L = 0b00001101;  // CCPR1L:CCP1CON<5:4> = 52

	// DC1B1 & DC1B0 = 0, Lower nibble is all '1' to use the CCP1 in PWM mode.
	CCP1CON = 0x 0 F;
}

motor_start()
{
}
motor_stop()
{
}
motor_restart()
{
	// 1 Function to stop and start the motor to use a new power output value.
	motor_stop();
	motor_start();
}