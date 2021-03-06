#include <TimerLib_part2.h>
#include "msp.h"
volatile int n=0;

void Setup_Init(void){
    // initialize the seven segment display
    P2SEL0 =0;
    P2SEL1 =0;
    P2DIR |= (BIT4 | BIT5 | BIT6 | BIT7);

    P5SEL0 =0;
    P5SEL1 =0;
    P5DIR |= (BIT0 | BIT1 | BIT2 | BIT6);
}

void SysTick_Init_interrupt(void){
    SysTick->CTRL=0;
    SysTick->LOAD=(1500000-1);      //half-second delay between displaying numbers
    SysTick->VAL=0;
    SysTick->CTRL=0x07;
}

void SysTick_Handler (void) {
    //updates displayed number then increments
    CaseManager(n);
    if(n!=9)
        n++;
    else
        n=0;
}

void CaseManager (int n){
    // cases for each possible displayed number
    switch(n) {
    case 0 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT6 | BIT7 | BIT5);
        P5OUT |= (BIT1 | BIT2 | BIT0);
        break;
    case 1 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT7);
        P5OUT |= (BIT1);
        break;
    case 2 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT6 | BIT7 | BIT4);
        P5OUT |= (BIT2 | BIT0);
        break;
    case 3 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT6 | BIT7 | BIT4);
        P5OUT |= (BIT1 | BIT2);
        break;
    case 4 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT7 | BIT4 | BIT5);
        P5OUT |= (BIT1);
        break;
    case 5 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT6 | BIT4 | BIT5);
        P5OUT |= (BIT1 | BIT2);
        break;
    case 6 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT6 | BIT4 | BIT5);
        P5OUT |= (BIT1 | BIT2 | BIT0);
        break;
    case 7 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT6 | BIT7);
        P5OUT |= (BIT1);
        break;
    case 8 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT6 | BIT7 | BIT4 | BIT5);
        P5OUT |= (BIT1 | BIT2 | BIT0);
        break;
    case 9 :
        P2OUT=0;
        P5OUT=0;
        P2OUT |= (BIT6 | BIT7 | BIT4 | BIT5);
        P5OUT |= (BIT1 | BIT2);
        break;
    }
}
