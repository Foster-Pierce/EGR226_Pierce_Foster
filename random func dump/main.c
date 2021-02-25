#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}

/****| DebounceSwitch2 | *****************************************
 * Brief: Debouncing function for when the button is not pressed, so
 * that no noise is contributed to the output of other functions.
 * param: void
 * return: int; 1 if successful, 0 if not
 *************************************************************/
int DebounceSwitch2(void)
{
    int pin_Value = 0;
    if ((P4IN & BIT6) == BIT6)
    {
        SysTick_delay(10);
        if ((P4IN & BIT6) == BIT6)
            pin_Value = 1;
    }
    return pin_Value; //return 1 if not pushed- 0 if pushed
}

/****| DebounceSwitch2 | *****************************************
 * Brief: Debouncing function for when the button is not pressed, so
 * that no noise is contributed to the output of other functions.
 * param: void
 * return: int; 1 if successful, 0 if not
 *************************************************************/
int DebounceSwitch2Rev(void)
{
    int pin_Value = 0;
    if ((P4IN & BIT7) == BIT7)
    {
        SysTick_delay(10);
        if ((P4IN & BIT7) == BIT7)
            pin_Value = 1;
    }
    return pin_Value; //return 1 if not pushed- 0 if pushed
}
