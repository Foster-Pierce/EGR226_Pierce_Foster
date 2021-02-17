#include "msp.h"

int DebounceSwitch1(void);
int DebounceSwitch2(void);

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

        while(DebounceSwitch2());
        while(DebounceSwitch1()){
            if((P2OUT & BIT2)==BIT2){
                P2OUT ^= BIT2;
            }
            P2OUT ^= BIT0;
        }
        while(DebounceSwitch2());
        while(DebounceSwitch1()){
            if((P2OUT & BIT0)==1)
                P2OUT ^= BIT0;

            P2OUT ^= BIT1;

        }
        while(DebounceSwitch2());
        while(DebounceSwitch1()){
            if((P2OUT & BIT1)==BIT1)
                P2OUT ^= BIT1;

            P2OUT ^= BIT2;

        }
    }
}

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