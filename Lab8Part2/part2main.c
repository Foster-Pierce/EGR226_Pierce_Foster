#include "msp.h"
#include <TimerLib_part2.h>
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	Setup_Init();
//	MotorSpeed();
	while(1){

	}
}
