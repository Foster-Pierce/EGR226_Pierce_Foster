#include <TimerLib_part3.h>
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

    // configure P4.2 as simple I/O SWITCH 1 (RED)
    P4SEL1 &= ~BIT2;
    P4SEL0 &= ~BIT2;
    P4DIR &= ~BIT2;
    P4REN |= BIT2;
    P4OUT |= BIT2;
    P4IES |= BIT2;
    P4IE |= BIT2;
    P4IFG = 0;

    // configure P4.3 as simple I/O SWITCH 2 (GREEN)
    P4SEL1 &= ~BIT3;
    P4SEL0 &= ~BIT3;
    P4DIR &= ~BIT3;
    P4REN |= BIT3;
    P4OUT |= BIT3;
    P4IES |= BIT3;
    P4IE |= BIT3;
    P4IFG = 0;
}

void debouncer(void){
    // initialize TimerA with interrupts for 10s
    TIMER_A2->CCR[0] = 30001;
    TIMER_A2->CCR[4] = 30000;
    TIMER_A2->CCTL[4] = 0x10;
    TIMER_A2->CTL = 0x0254;

}
void TA2_N_IRQHandler(void){
    //if green (increment) button was pressed
    if((P4IN & BIT3) == 0){
        if(n!=9)
            n++;
        else
            n=0;
        CaseManager(n);     //updates 7-segment display to current number
    }
    //if red (decrement) button was pressed
    else if((P4IN & BIT2) == 0){
        if(n!=0)
            n--;
        else
            n=9;
        CaseManager(n);     //updates 7-segment display to current number
    }
    TIMER_A2->CTL=0;        //disables TimerA and interrupt flag
    TIMER_A2->CCTL[4]=0;
}

void PORT4_IRQHandler (void){   // port 4 service routine (buttons)
    debouncer();            //timer enabled with interrupts begin running for 10ms delay
    P4IFG=0;
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
