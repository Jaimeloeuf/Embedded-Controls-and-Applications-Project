/* The target board uses 4 MHz oscillator module */
// Set 'Fosc' frequency, needed by the delay function call
#define _XTAL_FREQ 4000000
// PIC18F4520 Configuration Bit Settings
#pragma config OSC = XT  // Oscillator Selection bits (XT oscillator)
#pragma config LVP = OFF // Single-Supply ICSP Enable bit
#pragma config WDT = OFF // Watchdog Timer Enable bit

#include <xc.h>
#include <stdlib.h> // Used for itoa function
#include <stdint.h> // Used to get definition for uint8_t and other standard types. To convert to use primitives ltr.

// My own header files for the libs/modules
#include "LCD.h"	// LCD interface lib
#include "menu.h"
#include "Keypad.h"  // Keypad reader interface
#include "pwm.h"
//#include "adc.h"	// ADC control and reader functions
//#include "timer.h"  // Peripheral timer controller

/*	@Doc
    This is the main file, and it should only contain the:
    - main function
    - The interrupt service routines
    - Interrupt setup code
    - Power management code
    All other functionalities should be imported in from other libs.

	Idle mode means, CPU clock sleeps and peripheral continue to work. Sleep mode means, all selected oscillators stop.
 */

// The ISR is just a 'Switch' in charge of calling the "ISR" of the different libs/modules

void interrupt ISR(void) {
    /*	The ISR in this file will handle the interrupt source checking and clearing of the interrupt flag when done.
        @Steps
        1. Check for interrupt source by checking all the interrupt flags.
        2. Call the "ISR" functions
            Clear the interrupt flag.
     */

    if (keyFlag) // Check if DA went high
    {
        menu_disp(2, 0);
        // call the Keypad interrupt function
        keypad_ISR();
        // Clear the interrupt flag
        keyFlag = 0;
    } else if (INTCONbits.RBIF) {
        // If there is a change on PORTB pins RB 4-7
        // Check which pin it came from
        if (PORTBbits.RB4 == 0) {
            // next();
        } else if (PORTBbits.RB5 == 0) {
            // previous();            
        }
    } else if (INTCON3bits.INT1IF) {
        // If the Touch Sensor has been touched on INT1
        // Toggle the current state of the motor
        motor_toggle();
        menu_disp(3, 0);
    }        //	else if (adcFlag)
        //	{
        //		// Call the ADC interrupt function and get the adc value back
        //		adc_ISR();
        //		// Clear the interrupt flag
        //		adcFlag = 0;
        //	}
        //	else if (timeFlag)
        //	{
        //		// Timer overflow interrupt set.
        //		// The functions and everything else is dealt with in the Timer function.
        //		timer_ISR();
        //
        //		// Clear the interrupt flag
        //		timeFlag = 0;
        //	}
        ////	else if (/* Other interrupt flags... */)
        ////	{
        ////	}
    else {
        // If the source cannot be determined, set error flag
        menu_disp(5, 1);
    }
}

void interrupt low_priority ISR_low(void) {
    if (TMR0IF == 1) {

        // Clear the timer interrupt flag.
        TMR0IF = 0;
    }
}

void interrupt_setup() {
    // Disable all Interrupts
    GIE = 0;
//    INTCONbits.GIEH = 0;

    // Enable priority levels on interrupts
    RCONbits.IPEN = 1;

    /* INT1 for the touch sensor */
    // Clear the INT1 flag first
    INTCON3bits.INT1IF = 0;
    // Enable INT1
    INTCON3bits.INT1IE = 1;
    // Interrupt on falling edge from 5v to 0v
    INTCON2bits.INTEDG1 = 0;


//    /* PORTB INT on change high priority by default */
//    // Clear the PORTB INT on change INT flag
//    INTCONbits.RBIF = 0;
//    // Enable PORTB INT on change 
//    INTCONbits.RBIE = 1;

    // Enable all interrupts
    GIE = 1;
}

#define RIGHT PORTCbits.RC1
#define LEFT PORTCbits.RC0

void main(void) {
    ADCON1 = 0x0F;
    TRISA = 0b11000000;
    TRISB = 0b11110111;
    TRISD = 0x0f;
    TRISE = 0x0c;

    // Call all the initialization functions
//    interrupt_setup();  // This shit is fucking up everything
    /* INT1 for the touch sensor */
    // Clear the INT1 flag first
    INTCON3bits.INT1IF = 0;
    // Enable INT1
    INTCON3bits.INT1IE = 1;
    // Interrupt on falling edge from 5v to 0v
    INTCON2bits.INTEDG1 = 0;
    
    Init_LCD();
    Keypad_setup();
    motor_setup();

    // Print out the Main menu at the start of the program
    menu_disp(0, 0);
    __delay_ms(4000);
    motor_start();
    __delay_ms(3000);
//    motor_stop();
    motor_toggle();

    // To use OSSCON register to select the current run mode at startup

    // Call all the setup functions.
    // interrupt_setup();
    // Init_LCD();
    // Keypad_setup();

    // Do stuff here that I want to do before going back to sleep... can be anything.


    /*	Infinite loop so when it wakes and finishes the ISR and continue on the sleep line, it will loop
        back to go sleep again. This is done to prevent the program from ending after waking from sleep. */
    while (1) { SLEEP(); } // Go back to sleep after finnishing the Interrupt Routines.
}