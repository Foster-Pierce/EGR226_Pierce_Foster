/**************************************************************************************
* Author: Pierce Foster
* Course: EGR 226 - 905
* Date: 02/19/2021
* Project: Lab 4 Part 2
* File: part2main.c
* Description: This code makes the LED cycle through red, green, and blue while the button
* is being pressed. This includes debouncing functions to ensure the inputs are correct.
**************************************************************************************/
#include "msp.h"

int DebounceSwitch1(void);
int DebounceSwitch2(void);
void LEDcycle(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    //Configure GPIO

    P1SEL1 &= ~BIT1; // configure P1.1 as simple I/O
    P1SEL0 &= ~BIT1;
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;

    P2SEL1 &= ~BIT0; // configure P2.0 as simple I/O
    P2SEL0 &= ~BIT0;
    P2DIR |= BIT0;
    P2REN &= ~BIT0;
    P2OUT &= ~BIT0;

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
        while(DebounceSwitch2());

        if(((P2OUT & BIT0)||(P2OUT & BIT1)||(P2OUT & BIT2))==0){
            while(DebounceSwitch1()){

                P2OUT ^= BIT0;
                __delay_cycles(3000000);
                if(DebounceSwitch1()){
                    P2OUT ^= BIT0;
                    P2OUT ^= BIT1;
                }
                __delay_cycles(3000000);
                if(DebounceSwitch1()){
                    P2OUT ^= BIT1;
                    P2OUT ^= BIT2;
                }
                __delay_cycles(3000000);
                if(DebounceSwitch1())
                    P2OUT ^= BIT2;
            }
        }
        else
            LEDcycle();
    }
}
/****| LEDcycle | *****************************************
* Brief: When the LED is R, G, or B the program changes
* color based on what color it starts at.
* param: void
* return: void
*************************************************************/
void LEDcycle(void){
    int red = P2OUT & BIT0;
    int green = P2OUT & BIT1;
    int blue = P2OUT & BIT2;

    // if LED starts RED
    if(red==BIT0){
        while(DebounceSwitch1()){

            P2OUT &=~ BIT0;
            P2OUT ^= BIT1;
            __delay_cycles(3000000);
            if(DebounceSwitch1()){
                P2OUT ^= BIT1;
                P2OUT ^= BIT2;
            }
            __delay_cycles(3000000);
            if(DebounceSwitch1()){
                P2OUT ^= BIT2;
                P2OUT ^= BIT0;
            }
            __delay_cycles(3000000);

        }
    }

    // if LED starts GREEN
    else if(green==BIT1){
        while(DebounceSwitch1()){

            P2OUT &=~ BIT1;
            P2OUT ^= BIT2;
            __delay_cycles(3000000);
            if(DebounceSwitch1()){
                P2OUT ^= BIT2;
                P2OUT ^= BIT0;
            }
            __delay_cycles(3000000);
            if(DebounceSwitch1()){
                P2OUT ^= BIT0;
                P2OUT ^= BIT1;
            }
            __delay_cycles(3000000);

        }
    }

    // if LED starts BLUE
    else if(blue==BIT2){
        while(DebounceSwitch1()){

            P2OUT &=~ BIT2;
            P2OUT ^= BIT0;
            __delay_cycles(3000000);
            if(DebounceSwitch1()){
                P2OUT ^= BIT0;
                P2OUT ^= BIT1;
            }
            __delay_cycles(3000000);
            if(DebounceSwitch1()){
                P2OUT ^= BIT1;
                P2OUT ^= BIT2;
            }
            __delay_cycles(3000000);

        }
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
