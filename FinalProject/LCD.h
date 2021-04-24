#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

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
