#include <xc.h>
#include "timer.h"
#include "global_state.h"
#include "adc.h"
#include "pwm.h"

/* A timer is a clock oscillator feeding a counter.
 * The pre-scaler goes between the clock and counter, for the generation of desired frequency.
 * The post-scaler goes after the counter, to manage the occurrence of the interrupt. */

/* Setup the timer registers in this function */
void timer_setup(void) {
    GIE = 0; // Disable all interrupts

    T0CON = 0b00000010; // Make sure Timer0 is off by default, set to 16-bit mode, 1:8 prescaler
    // Clear the timer flag
    INTCONbits.TMR0IF = 0;
    // Set timer0 to be a low priority interrupt
    INTCON2bits.TMR0IP = 0;
    // Enable the timer interrupt flag
    INTCONbits.TMR0IE = 1;

    // Clear all the Timer0 register
    TMR0H = 0;
    TMR0L = 0;
    // Make sure Timer0 is off and set to 16-bit mode.
    T0CON = 0b00000010;

    GIE = 1; // Enable all interrupts
    GIEL = 1; // Enable all low priority interrupts
}

// Function to start Timer0
void timer_start(void) {
    TMR0ON = 1; // Set on bit directly
}

// Function to start Timer0
void timer_stop(void) {
    TMR0ON = 0; // Set off bit directly
}

// Function that acts as the interrupt routine for the Timer0 overflow interrupt
void timer_ISR(void) {
    // Read the values from the adc and start/stop motor every timer interrupt
    if (adc_read() > threshold)
        motor_start();
    else
        motor_stop();
}