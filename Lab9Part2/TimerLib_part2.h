#ifndef TimerLib_H_INCLUDED
#define TimerLib_H_INCLUDED
/****| Setup_Init | *****************************************
 * Brief: Initializes the seven segment display
 * param: void
 * return: void
 *************************************************************/
void Setup_Init(void);

/****| SysTick_Handler | *****************************************
 * Brief: SysTick ISR, that updates the displayed number
 * param: void
 * return: void
 *************************************************************/
void SysTick_Handler (void);

/****| SysTick_Init_interrupt | *****************************************
 * Brief: Initializes SysTick to delay for a half second then interrupt
 * param: void
 * return: void
 *************************************************************/
void SysTick_Init_interrupt(void);

/****| CaseManager | *****************************************
 * Brief: Determines which number to display via the parameter
 * then selects the correct case to turn on that number
 * param: int; n, the number that is to be displayed
 * return: void
 *************************************************************/
void CaseManager (int n);

#endif
