#ifndef FuncsLib_H_INCLUDED
#define FuncsLib_H_INCLUDED

/****| Setup_Init | *****************************************
 * Brief: Initializes the seven segment display
 * param: void
 * return: void
 *************************************************************/
void Setup_Init(void);

/****| PORT3_IRQHandler | *****************************************
 * Brief: Port 3 ISR, that performs actions when a button is pressed
 * param: void
 * return: void
 *************************************************************/
void PORT3_IRQHandler(void);

/****|  T32_INT2_IRQHandler  | *****************************************
 * Brief: Determines which button was pressed, and then performs the
 * correct action, either stopping the motor or toggling the LEDs
 * param: void
 * return: void
 *************************************************************/
void T32_INT2_IRQHandler(void);

/****| adcsetup | *****************************************
 * Brief: Sets up the ADC for 14-bit resolution and stores
 * information at memory location 5.
 * param: void
 * return: void
 *************************************************************/
void adcsetup(void);

/****| Keypad_Read | *****************************************
 * Brief: Determines which button was pressed on the keypad
 * then returns the number code for that key
 * param: void
 * return: int; number code that was pressed
 *************************************************************/
int Keypad_Read(void);

/****| Keypad_init | *****************************************
 * Brief: Initializes all the ports and pins used
 * param: void
 * return: void
 *************************************************************/
void Keypad_init(void);

/****| Press_Convert | *****************************************
 * Brief: Converts the number pressed, to the respected duty
 * cycle number
 * param: int; n, key pressed number
 * return: double; DC, duty cycle number between 1 and 0,
 *************************************************************/
double Press_Convert(int n);

/****| adcsetup | *****************************************
 * Brief: Sets up the ADC for 14-bit resolution and stores
 * information at memory location 5.
 * param: void
 * return: void
 *************************************************************/
void adcsetup(void);

/****| MotorConfig | *****************************************
 * Brief: Configures the motor speed for desired duty cycle,
 * ran at 40 Hz
 * param: double: d, duty cycle percent 0>d<1
 * return: void
 *************************************************************/
void MotorConfig(double d);

/****| ServoConfig | *****************************************
 * Brief: Configures the Servo position to desired location
 * param: double: d, servo position
 * return: void
 *************************************************************/
void ServoConfig(int d);

/****| RGBConfig | *****************************************
 * Brief: Sets the brightness of the RGB light
 * param: double: n, red-1, green-2, blue-3
 * int: c, brightness between 0 and 9
 * return: void
 *************************************************************/
void RGBConfig(double d, int n);

#endif
