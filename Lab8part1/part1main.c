#include <TimerLib_part1.h>
#include "msp.h"
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    double duty=0.3;        //enter number between 0 and 1
    while(1){
        Systick_DutyCycle(duty);
    }
}
