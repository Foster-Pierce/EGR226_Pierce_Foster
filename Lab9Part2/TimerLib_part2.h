#ifndef TimerLib_H_INCLUDED
#define TimerLib_H_INCLUDED

void Setup_Init(void);
void SysTick_Handler (void);
void SysTick_Init_interrupt(void);
void CaseManager (int n);
#endif