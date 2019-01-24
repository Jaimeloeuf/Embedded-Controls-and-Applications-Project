#ifndef pwm_H
#define pwm_H

// ADC interrupt flag definition. Will be used by the ISR to check for Interrupt source.
#define adcFlag INT0IF
// Function to setup all the registers, ports and everything for ADC to be ready to start
void motor_setup(void);
// Call this function to start the ADC, when reading is complete, CPU will be interrupted with the IF, adcFlag
void adc_read(void);
// The function or routine that will be called when the source of the interrupt is from the ADC
int adc_ISR(void);

#endif