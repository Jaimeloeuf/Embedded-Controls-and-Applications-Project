# ECAPP-Project

#### Use case scenarios
User can control the sprinkler

Sprinkler strength/speed will be controlled by hardware PWM

ADC will read in value of temperature sensor to determine surrounding temp, if exceeded threshold,
call the sprinkler to turn it on.

Timer will be the one that emulates a setInterval function, and will call the ADC to read value every
now and then.

LCD will show constant updates to the user about the current system state

Use keypad if the user wants to control certain stuff.
^ Example a password perhaps, or maybe set something to use the
sprinkler at a set interval regardless of what is the temperature.

7Seg will be used to constantly called display the current temperature.
