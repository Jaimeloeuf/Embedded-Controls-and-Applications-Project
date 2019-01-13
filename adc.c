/*	@Doc
	This 'adc' library/module will be used to interface with the ADC.
	Call functions in here to set values to the ADC registers and to read values from the ADC
*/

#include <xc.h>

void ADC_setup()
{
	// Set ADC input pin/channel
	// Modify the TRIS registers to match above ADC input selection

	// @Todo to modify the below defaults.
	// Set analog input channel.
	ADCON0 = 0b00000001; // select analog channel 0 (AN0), ADC on
	ADCON1 = 0b00001101; // AN0 and AN1 only, internal voltage referencing
	ADCON2 = 0b10000001; // right justified, manual acquisition, Fosc/8
	TRISA = 0b11111111;  // Port A as inputs
}

int adc_read_value()
{
	// Function that returns the current analog value read from the ADC
	// Should this wait for the value to be read finnish or should interrupts be used?

	ADCON0bits.CHS0 = ~ADCON0bits.CHS0; // Toggle selection of AN0 and AN1
	_delay(8);							// Delay for Acquisition time 8µs (>=5µs)
	ADCON0bits.GO = 1;					// Start A/D conversion
	while (ADCON0bits.DONE); 			// ADC completed?
	if (ADCON0bits.CHS0 == 0)
		TA = ADRESH * 256 + ADRESL; // keep result in TA
	else
		TB = ADRESH * 256 + ADRESL;
}