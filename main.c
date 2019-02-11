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
#include "adc.h"	// ADC control and reader functions
#include "timer.h"  // Peripheral timer controller

/*	@Doc
    This is the main file, and it should only contain the:
    - main function
    - The interrupt service routines
    - Interrupt setup code
    - Power management code
    All other functionalities should be imported in from other libs.

    Idle mode means, CPU clock sleeps and peripheral continue to work. Sleep mode means, all selected oscillators stop.
 */
int count = 0;

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
        // call the Keypad interrupt function
        keypad_ISR();
        // Clear the interrupt flag
        keyFlag = 0;
    } else if (INTCONbits.RBIF) {
        // If there is a change on PORTB pins RB 4-7
        // Check which pin it came from
        __delay_ms(10);
        // Always display the next or previous highest level menu
        if (PORTBbits.RB4 == 0)
            previous(); // s7
        else if (PORTBbits.RB5 == 0)
            next(); // s8

        // Clear the interrupt flag
        INTCONbits.RBIF = 0;
    } else if (INTCON3bits.INT2IF) {
        // If the Touch Sensor has been touched on INT1
        // Toggle the current state of the motor
        //        motor_toggle();
        motor_speed(1);
        // Clear the interrupt flag
        INTCON3bits.INT2IF = 0;
    } else {
        // If the source cannot be determined, set error flag
        menu_disp(5, 1);
    }
}

void interrupt low_priority ISR_low(void) {
    if (timeFlag) {
        // Set the pre-load value again
        TMR0H = 0x3C;
        TMR0L = 0xB0; // TMR0H:L=0x3CB0 = 15536

        //         The functions and everything else is dealt with in the Timer function.
        //        timer_ISR();

        if (++count > 5) {
            // Reset the count variable
            count = 0;
            // Read the values from the adc
            adc_read();
        }
        //        adc_read();

        // Clear the interrupt flag
        timeFlag = 0;
    }
}

void interrupt_setup() {
    // Disable all Interrupts
    GIE = 0;

    // Enable priority levels on interrupts
    RCONbits.IPEN = 1;

    /* PORTB INT on change high priority by default */
    // Clear the PORTB INT on change INT flag
    INTCONbits.RBIF = 0;
    // Enable PORTB INT on change 
    INTCONbits.RBIE = 1;

    // Enable all interrupts
    GIE = 1;
}

void toggle_switch_setup(void) {
    /* INT1 for the touch sensor */
    TRISB = 0xFF;
    // Disable all Interrupts
    GIE = 0;

    // Clear the INT1 flag first
    INTCON3bits.INT2IF = 0;
    // Enable INT1
    INTCON3bits.INT2IE = 1;
    // Interrupt on falling edge from 5v to 0v
    INTCON2bits.INTEDG2 = 0;

    // Enable all interrupts
    GIE = 1;
}

void main(void) {
    // To use OSSCON register to select the current run mode at startup

    // Call all the initialization/setup functions.
    interrupt_setup();
    toggle_switch_setup();
    Init_LCD();
    Keypad_setup();
    motor_setup();
    ADC_setup();

    // Print out the Main menu at the start of the program
    menu_disp(0, 0);

    // Setup timer the last as it will start running the moment it it set
//    timer_setup();



    /*	Infinite loop so when it wakes and finishes the ISR and continue on the sleep line, it will loop
        back to go sleep again. This is done to prevent the program from ending after waking from sleep.
        Cannot put sleep causes error*/
    while (1) {
                adc_read();
                __delay_ms(400);
    }
}