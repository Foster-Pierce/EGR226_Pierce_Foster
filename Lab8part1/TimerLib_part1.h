#define LCD_setup_H_INCLUDED

/****| Setup_Init | *****************************************
 * Brief: Initializes the GPIO pin
 * param: void
 * return: void
 *************************************************************/
void Setup_Init(void);
/****| Systick_DutyCycle | *****************************************
 * Brief: Sets the on and off times, and creates PWM
 * param: double; n, duty cycle number
 * return: void
 *************************************************************/
void Systick_DutyCycle(double n);
/****| Systick_ms_delay | *****************************************
 * Brief: Delay using Systick per millisecond
 * param: int n: number of milliseconds to delay
 * return: void
 *************************************************************/
void Systick_ms_delay(int n);
