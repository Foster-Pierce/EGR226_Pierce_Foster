#define LCD_setup_H_INCLUDED
#include <stdio.h>

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
/****| PrintChar | *****************************************
 * Brief: Prints the desired line of characters to the LCD
 * param: int: number of the row needed to be printed
 * return: void
 *************************************************************/
void PrintChar(void);
/****| UpdateTemp | *****************************************
 * Brief: Updates the temperature, in celsius, on the LCD
 * param: double; t, the temperature that is converted from
 * the TMP36
 * return: void
 *************************************************************/
void UpdateTemp(double t);
