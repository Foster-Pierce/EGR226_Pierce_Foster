/**************************************************************************************
* Author: Pierce Foster
* Course: EGR 226 - 905
* Date: 02/19/2021
* Project: Lab 4 Part 1
* File: part1main.c
* Description: This code makes the LED cycle through red, green, and blue when the button
* is pressed once, and stays on that color if the button is held down.
**************************************************************************************/
#include "msp.h"

int DebounceSwitch1(void);
int DebounceSwitch2(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    //Configure GPIO

    P1SEL1 &= ~BIT1; // configure P1.1 as simple I/O
    P1SEL0 &= ~BIT1;
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;

    P2SEL1 &= ~BIT0; // configure P2.0 as simple I/O
    P2SEL0 &= ~BIT0;
    P2DIR |= BIT0;
    P1REN &= ~BIT0;
    P1OUT &= ~BIT0;

    P2SEL1 &= ~BIT1; // configure P2.1 as simple I/O
    P2SEL0 &= ~BIT1;
    P2DIR |= BIT1;
    P2REN &= ~BIT1;
    P2OUT &= ~BIT1;

    P2SEL1 &= ~BIT2; // configure P2.2 as simple I/O
    P2SEL0 &= ~BIT2;
    P2DIR |= BIT2;
    P2REN &= ~BIT2;
    P2OUT &= ~BIT2;


    while(1){
        //first press
        while(DebounceSwitch2());

        if((P2OUT & BIT2)==BIT2){
            P2OUT ^= BIT2;
        }
        P2OUT ^= BIT0;

        while(DebounceSwitch1());
        while(DebounceSwitch2());

        //second press
        if((P2OUT & BIT0)==1)
            P2OUT ^= BIT0;

        P2OUT ^= BIT1;

        while(DebounceSwitch1());
        while(DebounceSwitch2());

        //third press
        if((P2OUT & BIT1)==BIT1)
            P2OUT ^= BIT1;

        P2OUT ^= BIT2;

        while(DebounceSwitch1());
    }
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
    if ((P1IN & BIT1) == 0)
    {
        __delay_cycles(30000);
        if ((P1IN & BIT1) == 0)
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
    if ((P1IN & BIT1) == BIT1)
    {
        __delay_cycles(30000);
        if ((P1IN & BIT1) == BIT1)
            pin_Value = 1;
    }
    return pin_Value; //return 1 if not pushed- 0 if pushed
}
