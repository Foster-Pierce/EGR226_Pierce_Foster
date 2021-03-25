#include <TimerLib_part2.h>
#include "msp.h"
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    Setup_Init();
    SysTick_Init_interrupt();
    __enable_interrupt();
    while(1){

    }
}
