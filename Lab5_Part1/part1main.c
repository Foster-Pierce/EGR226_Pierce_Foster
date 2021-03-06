/**************************************************************************************
 * Author: Pierce Foster
 * Course: EGR 226 - 905
 * Date: 02/26/2021
 * Project: Lab 5 Part 1
 * File: part1main.c
 * Description: This code makes the LED cycle through red, yellow, and green when the button
 * is pressed once, and stays on that color if the button is held down.
 **************************************************************************************/
#include "msp.h"

void Initialize(void);
int DebounceSwitch1(void);
int DebounceSwitch2(void);
void SysTick_delay(int n);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    Initialize();

    while(1){
        //first press
        while(DebounceSwitch2());

        if((P4OUT & BIT4)==BIT4){
            P4OUT ^= BIT4;
        }
        P4OUT ^= BIT0;

        while(DebounceSwitch1());
        while(DebounceSwitch2());

        //second press
        if((P4OUT & BIT0)==1)
            P4OUT ^= BIT0;

        P4OUT ^= BIT2;

        while(DebounceSwitch1());
        while(DebounceSwitch2());

        //third press
        if((P4OUT & BIT2)==BIT2)
            P4OUT ^= BIT2;

        P4OUT ^= BIT4;

        while(DebounceSwitch1());
    }
}
/****| Initialize | *****************************************
 * Brief: Initializes all the ports and pins used
 * param: void
 * return: void
 *************************************************************/
void Initialize(void){
    //Configure GPIO

    P4SEL1 &= ~BIT6; // configure P4.6 as simple I/O SWITCH
    P4SEL0 &= ~BIT6;
    P4DIR &= ~BIT6;
    P4REN |= BIT6;
    P4OUT |= BIT6;

    P4SEL1 &= ~BIT0; // configure P4.0 as simple I/O RED
    P4SEL0 &= ~BIT0;
    P4DIR |= BIT0;
    P4REN &= ~BIT0;
    P4OUT &= ~BIT0;

    P4SEL1 &= ~BIT2; // configure P4.2 as simple I/O YELLOW
    P4SEL0 &= ~BIT2;
    P4DIR |= BIT2;
    P4REN &= ~BIT2;
    P4OUT &= ~BIT2;

    P4SEL1 &= ~BIT4; // configure P4.4 as simple I/O GREEN
    P4SEL0 &= ~BIT4;
    P4DIR |= BIT4;
    P4REN &= ~BIT4;
    P4OUT &= ~BIT4;
}
/****| DebounceSwitch1 | *****************************************
 * Brief: Debouncing function for when the button is pressed, so
 * that no noise is contributed to the output of other functions.
 * param: void
 * return: int; 1 if successful, 0 if not
 *************************************************************/
int DebounceSwitch1(void)
{
    int pin_Value = 0;
    if ((P4IN & BIT6) == 0)
    {
        SysTick_delay(10);
        if ((P4IN & BIT6) == 0)
            pin_Value = 1;
    }
    return pin_Value; //return 1 if pushed- 0 if not pushed
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
/****| SysTick_delay | *****************************************
 * Brief: Delay using Systick per millisecond
 * param: int n: number of milliseconds to delay
 * return: void
 *************************************************************/
void SysTick_delay(int n){
    int i;
    SysTick->LOAD=(3000-1);
    SysTick->VAL=0;
    SysTick->CTRL=0x5;

    for(i=0;i<n;i++){
        while((SysTick->CTRL & BIT(16))==0);
    }

    SysTick->CTRL=0;

}
