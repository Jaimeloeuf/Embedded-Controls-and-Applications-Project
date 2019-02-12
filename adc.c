/*	@Doc
    This 'adc' library/module will be used to interface with the ADC.
    Call functions in here to set values to the ADC registers and to read values from the ADC
 */

#include <xc.h>
#include <stdint.h>
#include "pwm.h"
#define _XTAL_FREQ 4000000

void ADC_setup(void) {
    // Modify the TRIS registers to match ADC input selection
    TRISAbits.RA0 = 1; // Pin AN0/RA0 as input
    // Set analog input channel.
    ADCON0 = 0b00000001; // select analog channel 0 (AN0), ADC on
    ADCON1 = 0b00001110; // AN0 and AN1 only, internal voltage referencing
    ADCON2 = 0b00000100; // Result Right justified, manual acquisition time, Fosc/4
}

uint8_t adc_read(void) {
    __delay_ms(6); // Acquisition time 10us (>=5us)
    ADCON0bits.GO = 1; // Start ADC
    while (ADCON0bits.DONE); // Wait for ADC to complete
    return ADRESH;
}