#ifndef TimerLib_H_INCLUDED
#define TimerLib_H_INCLUDED
/****| Setup_Init | *****************************************
 * Brief: Initializes the seven segment display
 * param: void
 * return: void
 *************************************************************/
void Setup_Init(void);

/****| CaseManager | *****************************************
 * Brief: Determines which number to display via the parameter
 * then selects the correct case to turn on that number
 * param: int; n, the number that is to be displayed
 * return: void
 *************************************************************/
void CaseManager(int n);

/****| debouncer | *****************************************
 * Brief: Initializes a TimerA instance to delay for 10ms
 * then trigger an interrupt
 * param: void
 * return: void
 *************************************************************/
void debouncer(void);

/****| PORT4_IRQHandler | *****************************************
 * Brief: Port 4 ISR, that performs actions when a button is pressed
 * param: void
 * return: void
 *************************************************************/
void PORT4_IRQHandler(void);
/****| TA2_N_IRQHandler | *****************************************
 * Brief: Determines which button was pressed, and then increments
 * and displays the corect number, then turns off TimerA
 * param: void
 * return: void
 *************************************************************/
void TA2_N_IRQHandler(void);
#endif
