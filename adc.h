#ifndef adc_H
#define adc_H

// Function to setup all the registers, ports and everything for ADC to be ready to start
void ADC_setup(void);
// Call this function to start the ADC, when reading is complete, CPU will be interrupted with the IF, adcFlag
uint8_t adc_read(void);

#endif