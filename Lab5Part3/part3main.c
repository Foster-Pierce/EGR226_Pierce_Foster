/**************************************************************************************
 * Author: Pierce Foster
 * Course: EGR 226 - 905
 * Date: 02/19/2021
 * Project: Lab 5 Part 3
 * File: part2main.c
 * Description: This code makes the LED cycle through red, green, and blue while the button
 * is being pressed. This includes debouncing functions to ensure the inputs are correct.
 **************************************************************************************/
#include "msp.h"


//fix color names in LEDcyles (they are RGB not RYG) funcs and change func blocks, etc




int DebounceSwitch1(void);
int DebounceSwitch2(void);
int DebounceSwitch1Rev(void);
int DebounceSwitch2Rev(void);
void LEDcycle(void);
void LEDcycleReverse(void);
void SysTick_delay(int n);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    //Configure GPIO

    P4SEL1 &= ~BIT6; // configure P4.6 as simple I/O SWITCH 1 (BLACK)
    P4SEL0 &= ~BIT6;
    P4DIR &= ~BIT6;
    P4REN |= BIT6;
    P4OUT |= BIT6;

    P4SEL1 &= ~BIT7; // configure P4.7 as simple I/O SWITCH 2 (WHITE)
    P4SEL0 &= ~BIT7;
    P4DIR &= ~BIT7;
    P4REN |= BIT7;
    P4OUT |= BIT7;

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

    while(1){

        if(DebounceSwitch1())
            LEDcycle();

        else if(DebounceSwitch1Rev())
            LEDcycleReverse();

    }
}
/****| LEDcycle | *****************************************
 * Brief: When the LED is R, G, or B the program changes
 * color based on what color it starts at.
 * param: void
 * return: void
 *************************************************************/
void LEDcycle(void){
    int red = P4OUT & BIT0;
    int green = P4OUT & BIT2;
    int blue = P4OUT & BIT4;

    //if LED starts off
    if(((P4OUT & BIT0)||(P4OUT & BIT2)||(P4OUT & BIT4))==0){
        while(DebounceSwitch1()){

            P4OUT ^= BIT0;
            SysTick_delay(1000);
            if(DebounceSwitch1()){
                P4OUT ^= BIT0;
                P4OUT ^= BIT2;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1()){
                P4OUT ^= BIT2;
                P4OUT ^= BIT4;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1())
                P4OUT ^= BIT4;
        }

    }

    // if LED starts RED
    if(red==BIT0){
        while(DebounceSwitch1()){

            P4OUT &=~ BIT0;
            P4OUT ^= BIT2;
            SysTick_delay(1000);
            if(DebounceSwitch1()){
                P4OUT ^= BIT2;
                P4OUT ^= BIT4;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1()){
                P4OUT ^= BIT4;
                P4OUT ^= BIT0;
            }
            SysTick_delay(1000);

        }
    }

    // if LED starts GREEN
    else if(green==BIT2){
        while(DebounceSwitch1()){

            P4OUT &=~ BIT2;
            P4OUT ^= BIT4;
            SysTick_delay(1000);
            if(DebounceSwitch1()){
                P4OUT ^= BIT4;
                P4OUT ^= BIT0;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1()){
                P4OUT ^= BIT0;
                P4OUT ^= BIT2;
            }
            SysTick_delay(1000);

        }
    }

    // if LED starts BLUE
    else if(blue==BIT4){
        while(DebounceSwitch1()){

            P4OUT &=~ BIT4;
            P4OUT ^= BIT0;
            SysTick_delay(1000);
            if(DebounceSwitch1()){
                P4OUT ^= BIT0;
                P4OUT ^= BIT2;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1()){
                P4OUT ^= BIT2;
                P4OUT ^= BIT4;
            }
            SysTick_delay(1000);

        }
    }
}

void LEDcycleReverse(void){
    int red = P4OUT & BIT0;
    int green = P4OUT & BIT2;
    int blue = P4OUT & BIT4;

   // while(DebounceSwitch2Rev());
    //if LED starts off
    if(((P4OUT & BIT0)||(P4OUT & BIT2)||(P4OUT & BIT4))==0){
        while(DebounceSwitch1Rev()){

            P4OUT ^= BIT4;
            SysTick_delay(1000);
            if(DebounceSwitch1Rev()){
                P4OUT ^= BIT4;
                P4OUT ^= BIT2;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1Rev()){
                P4OUT ^= BIT2;
                P4OUT ^= BIT0;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1Rev())
                P4OUT ^= BIT0;
        }
    }

    // if LED starts RED
    if(red==BIT0){
        while(DebounceSwitch1Rev()){

            P4OUT &=~ BIT0;
            P4OUT ^= BIT4;
            SysTick_delay(1000);
            if(DebounceSwitch1Rev()){
                P4OUT ^= BIT4;
                P4OUT ^= BIT2;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1Rev()){
                P4OUT ^= BIT2;
                P4OUT ^= BIT0;
            }
            SysTick_delay(1000);

        }
    }

    // if LED starts GREEN
    else if(green==BIT2){
        while(DebounceSwitch1Rev()){

            P4OUT &=~ BIT2;
            P4OUT ^= BIT0;
            SysTick_delay(1000);
            if(DebounceSwitch1Rev()){
                P4OUT ^= BIT0;
                P4OUT ^= BIT4;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1Rev()){
                P4OUT ^= BIT4;
                P4OUT ^= BIT2;
            }
            SysTick_delay(1000);

        }
    }

    // if LED starts BLUE
    else if(blue==BIT4){
        while(DebounceSwitch1Rev()){

            P4OUT &=~ BIT4;
            P4OUT ^= BIT2;
            SysTick_delay(1000);
            if(DebounceSwitch1Rev()){
                P4OUT ^= BIT2;
                P4OUT ^= BIT0;
            }
            SysTick_delay(1000);
            if(DebounceSwitch1Rev()){
                P4OUT ^= BIT0;
                P4OUT ^= BIT4;
            }
            SysTick_delay(1000);

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

int DebounceSwitch1Rev(void)
{
    int pin_Value = 0;
    if ((P4IN & BIT7) == 0)
    {
        SysTick_delay(10);
        if ((P4IN & BIT7) == 0)
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
