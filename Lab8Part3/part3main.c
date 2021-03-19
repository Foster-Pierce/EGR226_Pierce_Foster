#include <TimerLib_part3.h>
#include "msp.h"
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	int press;
	double DC=0;
	Keypad_init();
	while(1){
	        press = Keypad_Read();      //assign key press to variable
	        DC=Press_Convert(press);    //convert key press to duty cycle number
	        if(press>=1)
	            MotorSpeed(DC);
	        SysTick_ms_delay(10);
	    }
}
