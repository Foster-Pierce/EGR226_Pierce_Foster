#include <TimerLib_part3.h>
#include "msp.h"
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    Setup_Init();
    NVIC_EnableIRQ(TA2_N_IRQn);
    NVIC_EnableIRQ(PORT4_IRQn);
    __enable_interrupt();
    while(1){

    }
}
