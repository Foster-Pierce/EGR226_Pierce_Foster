#ifndef TimerLib_H_INCLUDED
#define TimerLib_H_INCLUDED

void Setup_Init(void);
void SysTick_Init_interrupt(void);
void CaseManager(int n);
void debouncer(void);
void PORT4_IRQHandler(void);
void TA2_N_IRQHandler(void);
#endif
