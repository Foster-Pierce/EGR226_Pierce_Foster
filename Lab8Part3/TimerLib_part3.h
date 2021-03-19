#define LCD_setup_H_INCLUDED
/****| Setup_Init | *****************************************
 * Brief: Initializes the GPIO pin for PWM, and TimerA for PWM
 * param: void
 * return: void
 *************************************************************/
void Setup_Init(int duty);
/****| MotorSpeed | *****************************************
 * Brief: Calls the setup function and sets the duty cycle
 * param: double: duty, duty cycle amount, between 1 and 0
 * return: void
 *************************************************************/
void MotorSpeed(double x);
/****| Keypad_init | *****************************************
 * Brief: Initializes all the ports and pins used
 * param: void
 * return: void
 *************************************************************/
void Keypad_init(void);
/****| Keypad_Read | *****************************************
 * Brief: Determines which button was pressed on the keypad
 * then returns the number code for that key
 * param: void
 * return: int; number code that was pressed
 *************************************************************/
int Keypad_Read(void);
/****| Systick_ms_delay | *****************************************
 * Brief: Delay using Systick per millisecond
 * param: int n: number of milliseconds to delay
 * return: void
 *************************************************************/
void SysTick_ms_delay(int n);
/****| Press_Convert | *****************************************
 * Brief: Converts the number pressed, to the respected duty
 * cycle number
 * param: int; n, key pressed number
 * return: double; DC, duty cycle number between 1 and 0,
 *************************************************************/
double Press_Convert(int n);
