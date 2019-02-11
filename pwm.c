#include <xc.h>
#include "pwm.h"
#define _XTAL_FREQ 4000000

/*	@Doc
    This module contains the PWM control
    The operation of CCP1 module is controlled by register CCP1CON.
    For PWM mode, Timer2 is used for generating the switching frequency.
 */

// Motor state to keep track if motor is on or off. 0 for off and 1 for on.
char motor_state = 0;
// Speed variable keeps track of how fast the motor runs. 0 for half speed 1 for full speed
char speed = 0; // Start with half speed

void motor_setup(void) {
    // RC2 will be used as output, so set the pin usage type here. All other pins are left untouched by the bitmask
    TRISC &= 0xFB;
    // Set the output off first
    PORTC &= 0xFB;
}

void motor_speed(char input_speed) {
    if (input_speed == 1)
        speed = 1;
    else
        speed = 0;
}

/* For some reason the motor's pwm below works in the opposite way? Like halfspeed is faster than full speed
 Leaving it like this first because at least I have 2 speeds. */
void motor_start(void) {
    if (speed) {
        // If speed == 0 means half speed
        T2CON = 0b00000101; // On Timer 2, postscale = 1:1, prescale = 1:4
        PR2 = 62; // Set PR2 = 64 for 250 µs
        CCPR1L = 0b00010010; // CCPR1L:CCP1CON<5:4> = 75
        CCP1CON = 0b00111111;

    } else {
        // If speed == 1 means full speed
        T2CON = 0b00000101; // On Timer 2, postscale = 1:1, prescale = 1:4
        PR2 = 62; // Set PR2 = 64 for 250 µs
        CCPR1L = 0b00110010; // CCPR1L:CCP1CON<5:4> = 200
        CCP1CON = 0b00111111;
    }
    __delay_ms(100);
    motor_state = 1;
}

void motor_stop(void) {
    // Stop the motor by turning off the PWM mode
    CCP1CON = 0;
    // Make sure the output v on the pin is off
    PORTCbits.RC2 = 0;
    // Stop the timer from running
    T2CONbits.TMR2ON = 0;
    // Set current motor state as off
    motor_state = 0;
}

void motor_restart(void) {
    // 1 Function to stop and start the motor to use a new power output value.
    motor_stop();
    motor_start();
}

void motor_toggle(void) {
    // Toggle the current state of the 'motor' or PWM output
    // If motor is on, off it, else on it.
    if (motor_state)
        motor_stop();
    else
        motor_start();
}