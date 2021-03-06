#ifndef TimerLib_H_INCLUDED
#define TimerLib_H_INCLUDED

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

/****| PORT4_IRQHandler | *****************************************
 * Brief: Port 4 ISR, that performs actions when a button is pressed
 * param: void
 * return: void
 *************************************************************/
void PORT4_IRQHandler (void);

#endif
