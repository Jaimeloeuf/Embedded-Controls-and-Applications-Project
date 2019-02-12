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

    // Enable RD 0 - 1 as output
    TRISD &= 0xFC;
    // Make sure they both output 0 at the start
    PORTD &= 0xFC;

    GIE = 1; // Enable all interrupts
    GIEL = 1; // Enable all low priority interrupts
}

void timer_start(void) {
    T0CON = 0b10000010; // On Timer0, set to 16-bit mode,
    // TMR0ON = 1; // Set on bit directly
}

void timer_stop(void) {
    T0CON = 0b00000010; // Off Timer0
    // TMR0ON = 0; // Set off bit directly
}

void timer_ISR(void) {
    PORTDbits.RD0 ^= 1;
    PORTDbits.RD1 ^= 1;

    // Read the values from the adc
    if (adc_read() > threshold)
        motor_start();
    else
        motor_stop();
}