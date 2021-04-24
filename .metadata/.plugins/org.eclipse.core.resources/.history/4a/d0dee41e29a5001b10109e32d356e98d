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

/****| LCD_init | *****************************************
 * Brief: Initializes all the ports and pins used, along with
 * the LCD screen
 * param: void
 * return: void
 *************************************************************/
void LCD_init (void);

/****| PulseEnablePin | *****************************************
 * Brief: Pulses the enable pin low, then high, then low each
 * for 10us
 * param: void
 * return: void
 *************************************************************/
void PulseEnablePin (void);

/****| pushNibble | *****************************************
 * Brief: pushes a 4-bit portion of information to be used
 * instead of a full byte
 * param: void
 * return: void
 *************************************************************/
void pushNibble (int nibble);

/****| pushByte | *****************************************
 * Brief: Pushes the full byte of information without condensing
 * it into 4-bit chunks
 * param: int: nibble which is the 4-bit chunks of the byte
 * return: void
 *************************************************************/
void pushByte (int byte);

/****| write_command | *****************************************
 * Brief: parent function that takes the byte of data, and pushes
 * it through various child functions in order to pulse the enable
 * pin with the desired information
 * param: int: byte of data to be written as a command
 * return: void
 *************************************************************/
void write_command (int command);

/****| write_data | *****************************************
 * Brief: Initializes all the ports and pins used
 * param: int: command that sets the RS pin, then sends data
 * then clears the RS pin
 * return: void
 *************************************************************/
void write_data (int data);

/****| Systick_ms_delay | *****************************************
 * Brief: Delay using Systick per millisecond
 * param: int n: number of milliseconds to delay
 * return: void
 *************************************************************/
void Systick_ms_delay(int n);

/****| Systick_us_delay | *****************************************
 * Brief: Delay using Systick per microsecond
 * param: int n: number of microseconds to delay
 * return: void
 *************************************************************/
void Systick_us_delay(int n);

/****| SysTick_Init_interrupt | *****************************************
 * Brief: Initializes SysTick to delay for a half second then interrupt
 * param: void
 * return: void
 *************************************************************/
void SysTick_Init_interrupt(void);

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

/****| LCDPWM | *****************************************
 * Brief: Sets the brightness of the LCD, ran at 100 Hz
 * param: double: d, the input from the turning of the potentiometer
 * return: void
 *************************************************************/
void LCDPWM(double d);

/****| PrintMenu | *****************************************
 * Brief: Prints the desired text to the LCD, between the 5
 * different screens
 * param: int: t, the menu number
 * return: void
 *************************************************************/
void PrintMenu(int t);

/****| PrintMenu1 | *****************************************
 * Brief: Determines the correct menu to print, and calls PrintMenu
 * param: int: c, the line on the lcd
 * int: m, the menu number
 * return: void
 *************************************************************/
void PrintMenu1(int c, int m);

#endif
