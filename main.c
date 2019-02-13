/* The target board uses 4 MHz oscillator module */
// Set 'Fosc' frequency, needed by the delay function call
#define _XTAL_FREQ 4000000
// PIC18F4520 Configuration Bit Settings
#pragma config OSC = XT  // Oscillator Selection bits (XT oscillator)
#pragma config LVP = OFF // Single-Supply ICSP Enable bit
#pragma config WDT = OFF // Watchdog Timer Enable bit

#include <xc.h>
#include <stdlib.h> // Used for itoa function
#include <stdint.h> // Used to get uint8_t and other standard type definitions
/* My own header files for the lib/modules */
#include "LCD.h"	// LCD interface lib
#include "menu.h"   // Lib that stores all the menus with functions to display them
#include "Keypad.h"  // Keypad reader interface
#include "pwm.h"    // PWM output controller and motor control functions
#include "adc.h"	// ADC control and reader functions
#include "timer.h" // Peripheral timer controller
#include "global_state.h"  // Module that maintains all the stateful variables

/*	@Doc
    This is the main file, and it only contains the:
    - main function as program entry point
    - The interrupt service routine switcher
    - Interrupt setup codes
    - Power management setup code
    All other functionalities should be imported in from other libs or handled there.
 */

void interrupt ISR(void) {
    /*	This ISR is just a 'Switch' in charge of calling the "ISR" of the different libs/modules
        This ISR handles the interrupt source checking and clearing of interrupt flags when done.
        @Steps
        1. Check for interrupt source by checking all the interrupt flags.
        2. Call the "ISR" functions
        3. Clear the interrupt flag.
     */
    if (keyFlag) {
        // When DA goes high
        // Call the Keypad interrupt function
        keypad_ISR();
        // Clear the interrupt flag
        keyFlag = 0;
    } else if (INTCONbits.RBIF) {
        // If there is a change on PORTB pins RB 4-7. Check which pin it came from
        // Add a delay for switch de-bouncing
        __delay_ms(20);
        // Always display the next or previous highest level menu
        if (PORTBbits.RB4 == 0)
            previous(); // s7 pressed, navigate to previous menu
        else if (PORTBbits.RB5 == 0)
            next(); // s8 pressed, navigate to next menu
        // Clear the interrupt flag
        INTCONbits.RBIF = 0;
    } else if (INTCON3bits.INT2IF) {
        // If the Touch Sensor has been touched on INT1
        // Toggle the current state of the motor
        motor_toggle();
        // Change the operating mode to manual mode if not already manual mode.
        if (mode) {
            toggle_mode();
            // If user on menu2 when mode change caused by toggle state of motor
            if (c_menu == 2)
                // Display the menu again after updating the current mode
                menu_disp(2);
        }
        // Clear the interrupt flag
        INTCON3bits.INT2IF = 0;
    } else {
        // If the source cannot be determined, display error message on the LCD
        menu_disp(10);
    }
}

void interrupt low_priority ISR_low(void) {
    /*	This ISR is just a 'Switch' in charge of calling the "ISR" of the different libs/modules
        This ISR handles the interrupt source checking and clearing of interrupt flags when done.
        @Steps
        1. Check for interrupt source by checking all the interrupt flags.
        2. Call the "ISR" functions
        3. Clear the interrupt flag.
     
        Same functionality as the above ISR except that this handles low priority interrupts
     */
    if (timeFlag) {
        // Call the Timer interrupt function
        timer_ISR();
        // Clear the interrupt flag
        timeFlag = 0;
    }
}

// General "main" interrupt setup function
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

// Setup function for the motor toggle switch using the Touch Sensor
void toggle_switch_setup(void) {
    /* Use INT2 for the touch sensor */
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

// Function to setup the LED indicator lights
void indicators_setup(void) {
    // Enable RD 0 - 1 as output
    TRISD &= 0xFC;
    // Make sure they both output 0 at the start
    PORTD &= 0xFC;
    /* RED for Manual mode. Yellow for Auto mode */
    // Since the default mode is man, light up the RED led.
    man_LED = 1;
}

// Main function (Main entry point for the program)
void main(void) {
    // To use OSSCON register to select the current run mode at startup
    // Run the system in PRImary RUN mode
    OSCCON = 0;
    // Set IDLEN to enable the device to enter Idle mode when the sleep instruction is executed
    OSCCONbits.IDLEN = 1;

    // Call all the initialization/setup functions.
    interrupt_setup(); 
    toggle_switch_setup();
    Init_LCD();
    Keypad_setup();
    motor_setup();
    ADC_setup();
    indicators_setup();
    timer_setup();

    // Print out the Main menu at the start of the program
    menu_disp(0);

    /* Infinite loop so when it wakes and finishes the ISR and continue on the
     * sleep line, it will loop back to go sleep again. This is done to prevent
     * the program from ending after waking from sleep.
     * 
     * Idle mode means, CPU clock sleeps and peripheral continue to work.
     * Sleep mode means, all selected oscillators stop.
     * 
     * The below sleep command in the infinite loop puts the device into Idle
     * mode instead of Sleep mode as IDLEN bit is set
     */
    while (1) { Sleep(); }
}