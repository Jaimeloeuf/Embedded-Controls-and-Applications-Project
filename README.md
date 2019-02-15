# ECAPP-Project
This is an Embedded Systems and Controls Project for a sprinkler control system where the Sprinkler will be emulated a motor.
- The 'strength' or speed of the sprinkler that corresponds to the amount of water sprinkled out will be directly correlated with the speed of the motor.
- There are 2 predefined speeds for the motor.


## Use case scenarios
- To use this system, user can sets the mode for the system, either manual or auto mode, and use the predefined functionalities for these modes. The functionalites of the mode is described below.


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


#### Menu
- The menu options
	0.	Main menu, displays the way to navigate the menus
	1.	View current temperature (More precise than the nearest integer version displayed on the 7Seg)
	2.	Toggle operating mode
	3.	View current temperature threshold used in the automatic mode.
	4.	Set a new temperature threshold, used in the automatic mode.
	5.	Toggle sprinkler strength (If motor on when speed is changed, new speed will take effect immediately)

- Basic Navigation keys
	- To navigate the menu, press s7 to go back, press s8 to go next menu item
	- Press E for "enter". Pressing enter is equiv. to selecting the menu's option.
	- Press F as a "Finnish" key at anytime to go back to the main menu.

- Menu 1
	- Press E to view current temp.
	- After E is pressed to view current temp, E can still be pressed continuously to update the reading.
	- Press F to go back to the main menu.
- Menu 2
	- Press E to toggle current operating mode
	- E can be continously pressed to continously toggle the operating mode
	- Press F to go back to the main menu.
- Menu 3
	- Press E to view current temperature value threshold that will on the motor in auto mode
	- Press F to go back to the main menu.
- Menu 4
	- Press E to set new temperature threshold
	- After E, user can now enter a new value between 0-255 as the new threshold and press E again to set it.
	- Press F to go back to the main menu and quit the setting process.
- Menu 5
	- Press E to toggle motor output speed between Full speed and half speed
	- E can be continously pressed to continously toggle the motor speed
	- Press F to go back to the main menu.


#### How does the user uses it?
- To directly on or off the sprinkler:
	- Touch the touch sensor pad to toggle the motor mode/state.

- To set the temperature threshold for use in automatic mode.
	- Go to the 3rd option in the menu.
	- Enter a temperature in degree celcius. Press the 'D' for decimal point, how do I clear the input??
	- Press the 'F' key to indicate that you have finnished the input.
	- The new temperature threshold will display, and you be asked to confirm the option.
		- If confirmed, program will go back to the menu screen.
		- If not confirmed, program will loop back to let you enter the temp again.

- To set sprinkler strength.
	- Use the toggle speed sub menu in the menu
	- Press E to toggle the speed
	- Press the 'F' key to indicate that you have finnished the input.

	The keypad will only be used to do stuff in the menu.

- To wake the device from sleep mode:
	- Any actions will cause

#### Technical components usage
- Sprinkler strength/speed
	- controlled by the hardware PWM.
	- Timer 2 will be used for the PWM generation
- Temperature value
	- Read using the on chip ADC
	- Temperature sensor emulated by potentiometer/trimmer
- Sprinkler's Toggle switch
	- The touch sensor will be used. Touching it toggle's the current state of the sprinkler
- A setInterval function
	- Timer0 will used to acheive this.
	- At every interval a check for the temperature against the threshold will be ran
- System status updates for the user
	- LCD will be used to constantly display the current state of the system.
	- LEDs are used to show user the current operating mode
- Obtaining user's input
	- Use keypad if the user wants to control certain stuff.


### Pin definitions / usage:
RA0 / AN0
	ADC connected to the trimmer
RA5
	7Seg SL1
RB 0
	Keypad's DA external Interrupt pin
RB 2
	INT2 used as Touch Sensor external interrupt pin
RB 4 - 5
	The 2 push button used to move around in the menu as interrupt touch
RC2
	Hardware PWM to the motor
RC 4 - 7
	Keypad's encoder output A to D
RD 4 - 7
	LCD data
RE 0 - 1
	LCD Control pins


#### BITWISE OPERATIONS Cheatsheet
- Use the AND bitwise operator to set bits to 0 with a 0 as the mask
- Use the OR bitwise operator to set bits to 1 with a 1 as the mask
- Use the EXOR bitwise operator to toggle the bits with a 1 as the mask
- Use the NEGATE bitwise operator to toggle bits without any bitmask

So there will be a global variable to keep track of the current menu in the file so when an interrupt happens,
the state is still remembered and continues from there.