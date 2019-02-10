#ifndef pwm_H
#define pwm_H

// Function to setup all the registers, ports and everything for ADC to be ready to start
void motor_setup(void);

void motor_speed(char input_speed);
void motor_start(void);
void motor_stop(void);
void motor_restart(void);
void motor_toggle(void);

#endif