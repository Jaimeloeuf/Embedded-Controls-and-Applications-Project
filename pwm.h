#ifndef pwm_H
#define pwm_H

// Motor state to keep track if motor is on or off. 0 for off and 1 for on.
char motor_state = 0;
// Speed variable keeps track of how fast the motor runs. 0 for half speed 1 for full speed
char speed = 0; // Start with half speed

// Function to setup all the registers, ports and everything for ADC to be ready to start
void motor_setup(void);

void toggle_speed(void);
void motor_start(void);
void motor_stop(void);
void motor_restart(void);
void motor_toggle(void);

#endif