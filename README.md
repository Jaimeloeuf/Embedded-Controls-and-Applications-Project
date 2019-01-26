# ECAPP-Project

## Use case scenarios
- This is an IoT Project for a sprinkler control system and the Sprinkler will be emulated a motor. The 'strength' or speed of the sprinkler that corresponds to the amount of water sprinkled out will be directly correlated with the speed of the motor.
- To use this system, the user can set a mode for the system, either manual or auto mode. The functionalites of the mode is described below.
- Upon system startup and inactivity or lock, a password is needed to use the system again.

#### Modes
- Manual mode:
	User can set the strength of the sprinkler.
		If the sprinkler is on while the user set the strength, the sprinkler's strength will change on the spot.
	User can start and stop the sprinkler manually.
	User can can set a timer, to automatically off the sprinkler on timeout.

- Auto mode:
	At any point in time, the user can change mode by selecting mode change or by pressing on or off directly to swtich into manual mode.
	If on or off signals are sent to the system, then the mode will be automatically switched back to manual mode.
	User can set the strength of the sprinkler.
		At any time, the user can set a new strength but it will only be applied the next time the sprinkler turns on.
	On mode startup, a loop with a fixed interval will be started, at every interval, the check below will be performed, thus making the sprinkler start and stop depending on the current temperature.
		If the temperature exceeds user settable "threshold", then on the sprinkler.
		else off the sprinkler.
	At any point in time, the user can set a new interval length. After setting the countdown will restart with the new interval.
	At any point in time, the user can set a new temperature threshold, this value will only be


#### How tos:
- Sprinkler strength/speed
	- controlled by the hardware PWM.
- Temperature value
	- Read using the ADC on the Pic Chip from the temperature sensor breakout board
	- Sensor breakout board consist of a LM35 temperature sensor and a simple 10X amplifier.
	- Amp is need to make the reading more precise as the resolution of the ADC is not very high.
	- The ADC's reference voltage will be the positive power supply voltage of 5V and Gnd of 0V, thus resolution or step size is 4.88mV.
	- The range of expected output voltage from the temperature sensor is from 200mV to 500mV. A 10 times amplification can be used.
- On/Off control switch
	- The touch sensor can be used. If Sprinkler on when touched, off it and vice versa.
- A setInterval function
	- A Timer will used to acheive this.
	- At every interval a function the user chooses can be ran.
		- E.g. A function calling the ADC to read temperature value every 5 minutes.
- System status updates for the user
	- LCD will be used to constantly display the current state of the system.
	- 7Seg will be used to called constantly display the current temperature.
	- LEDs can be used to show user current status and more.
- Obtaining user's input
	- Use keypad if the user wants to control certain stuff.
- Password protection
	- Password hash stored inside the EEPROM will act as the DB to be queried.
		- The hashing function would need to be self-implemented.
		- Cannot be too complex and the hash cannot be too long.
	- Only users with the valid password can control the system.
	- The system will be auto-locked after 2 mins of inactivity.
	- The system will be auto-locked at startup.
	- The system can be locked by the user.
- Longterm memory of the user's settings.
	- E.g. Every time I set a new interval, the next time I startup the system I want it to be the one I last set.



### Pin definitions:
RA0 / AN0
	ADC
RA 1 - 4
	LCD data
RA5
	7Seg SL1
<!-- RB 0
	DA Interrupt pin -->
<!-- RB 1
	On/Off pin with interrupt -->
RC2
	Hardware PWM
<!-- RC 4 - 7
	Keypad -->
RD 0 - 7
	7Seg output pins
<!-- RE 0 - 1
	LCD Control pins -->
RE2
	7Seg SL2


#### PINS LEFT
<!-- RA 5 -->
RB 2 - 5
RC 0 - 1, 3
<!-- RD 0 - 7 -->
<!-- RE 2 -->