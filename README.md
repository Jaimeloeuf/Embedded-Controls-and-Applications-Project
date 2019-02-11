# ECAPP-Project
This is an IoT Project for a sprinkler control system where the Sprinkler will be emulated a motor.
- The 'strength' or speed of the sprinkler that corresponds to the amount of water sprinkled out will be directly correlated with the speed of the motor.
- There are 2 predefined speeds for the motor.


## Use case scenarios
- To use this system, the user can set a mode for the system, either manual or auto mode. The functionalites of the mode is described below.


#### Modes
- Manual mode:
	- User can choose 1 of 2 strength for the sprinkler.
		- If sprinkler on while setting strength, the sprinkler's strength will change on the spot.
	- User can start and stop the sprinkler manually using the touch sensor
	- User can can set a timer, to automatically off the sprinkler on timeout.

- Auto mode:
	- At any point in time, mode can be changed by selecting mode change or by pressing the toggle switch directly to swtich toggle the sprinkler and change into manual mode.
	- User can set the strength of the sprinkler.
		- At any time, the user can set a new strength and the sprinkler will restart
	- On mode startup, a loop with a fixed interval will be started, at every interval, the check below will be performed, thus making the sprinkler start and stop depending on the current temperature.
		- If the temperature exceeds user settable "threshold", then on the sprinkler, else off the sprinkler.
	- At any point in time, the user can set a new temperature threshold, this value will only be used on the next threshold checking.


#### How does the user uses it?
*** Menu
1.	View current temperature (More precise than the nearest integer version displayed on the 7Seg)
2.	Toggle operating mode
3.	View current temperature threshold used in the automatic mode.
4.	Set a new temperature threshold, used in the automatic mode.
5.	Set sprinkler strength when on (If sprinkler is on when the speed is set, the new speed will take effect immediately)

To navigate the menu, press s3 to go back, press s2 to go next menu item
Before going to sleep, set the LCD to display,
	Last recorded temperature: .. 30C
then off the 7seg and go to sleep.

- To wake the device from sleep mode:
	- Touch the touch sensor pad to wake the system up.
	- Note that the system will go back to sleep after 10 seconds of inactivity.
	- To tell if the device is sleeping, look at the 7Seg, if it is displaying the current temp, then it is awake, and asleep otherwise.

- To directly on or off the sprinkler:
	- Touch the touch sensor pad to toggle the motor mode/state.
	- Note that this will only work when the device is awake, meaning after the device wakes up.

- To set the temperature threshold for use in automatic mode.
	- Go to the 3rd option in the menu.
	- Enter a temperature in degree celcius. Press the 'D' for decimal point, how do I clear the input??
	- Press the 'F' key to indicate that you have finnished the input.
	- The new temperature threshold will display, and you be asked to confirm the option.
		- If confirmed, program will go back to the menu screen.
		- If not confirmed, program will loop back to let you enter the temp again.

- To set sprinkler strength.
	- Press the '' key on the keypad to go into the speed/strength setting menu.
	- Enter a number up to 100 on the keypad denoting strength in percentage
	- Press the 'F' key to indicate that you have finnished the input.

	The keypad will only be used to do stuff in the menu.


#### Technical components usage
- Sprinkler strength/speed
	- controlled by the hardware PWM.
	- Timer 2 will be used for the PWM generation
- Temperature value
	- Read using the on chip ADC
- Sprinkler's Toggle switch
	- The touch sensor will be used. Touching it toggle's the current state of the sprinkler
- A setInterval function
	- A Timer will used to acheive this.
	- At every interval a function the user chooses can be ran.
		- E.g. A function calling the ADC to read temperature value every 5 minutes.
- System status updates for the user
	- LCD will be used to constantly display the current state of the system.
	- 7Seg will be used to called constantly display the current temperature, Rounded to the nearest integer
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
RB 0
	DA Interrupt pin
RB 1
	Touch Sensor interrupt
RB 4 - 5
	The 2 push button used to move around in the menu as interrupt touch
RC2
	Hardware PWM
RC 4 - 7
	Keypad
RC
	The remaining RC/PORTC pins can be used to connect the LEDs to show the current mode and stuff.
RD 0 - 7
	7Seg output pins
RE 0 - 1
	LCD Control pins
RE2
	7Seg SL2


#### PINS Unused
RA 5
RB 2 - 5
RC 0 - 1, 3
RD 0 - 7
RE 2


<!-- Example code for ADC -->
<!-- ADCON0 = 0b00000001;
ADCON1 = 0b00001110;
ADCON2 = 0b00010001;

ADCON0bits.GO = 1;
while (ADCON0bits.DONE);
result = ADRESH >> 6;
PORTA = result;

T2CON = 0b00000111;
PR2 = 78;
CCPR1L = 0b00100011;
CCP1CON = 0b00001100;

TMR2ON = 0; -->


#### BITWISE OPERATIONS Cheatsheet
- Use the AND bitwise operator to set bits to 0 with a 0 as the mask
- Use the OR bitwise operator to set bits to 1 with a 1 as the mask
- Use the EXOR bitwise operator to toggle the bits with a 1 as the mask
- Use the NEGATE bitwise operator to toggle bits without any bitmask

So there will be a global variable to keep track of the current menu in the file so when an interrupt happens,
the state is still remembered and continues from there.