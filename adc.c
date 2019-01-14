/*	@Doc
	This 'adc' library/module will be used to interface with the ADC.
	Call functions in here to set values to the ADC registers and to read values from the ADC
*/

#include <xc.h>

void ADC_setup(void)
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

void adc_read(void)
{
	// Calll function to read value from the ADC.
	// Should this function take in an arguement to determine the analog channel to read frm?
	
	// Start acquisition
	ADCON0bits.CHS0 = ~ADCON0bits.CHS0; // Toggle selection of AN0 and AN1
	// Delay for Acquisition time 8µs (>=5µs)
	_delay(8);

	// Start A/D conversion
	ADCON0bits.GO = 1;
	// Wait for ADC to complete. None Interrupt flag method.
	while (ADCON0bits.DONE);
}

int adc_ISR(void)
{
	// "ISR" that returns the value read from the (ADCRH + ADCRL)

	if (ADCON0bits.CHS0 == 0)
		TA = ADRESH * 256 + ADRESL; // keep result in TA
	else
		TB = ADRESH * 256 + ADRESL;
}